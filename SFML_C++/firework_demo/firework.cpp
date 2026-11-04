#include "includes/firework.hpp"
#include <cmath>

const float FIREWORK_PARTICLE_SIZE = 2.0f;
const float ROCKET_FLIGHT_MULT = 2.0f;
const float ROCKET_FLIGHT_MIN = 1.0f;
const float ROCKET_RADIUS = 2.0f;
const float EASE_POWER = 2.0f;
const float FIREWORK_MAX_SCALE = 1.5f;
const float FUSE_MULT = 0.1f;
const float FUSE_MIN = 0.5f;

Firework::Firework(const sf::Vector2f& origin,
                   const sf::Vector2f& destination,
                   std::vector<sf::Image*>* patterns)
    : vDestination(destination),
      vOrigin(origin),
      vPosition(origin),
      fLifetime(0.0f),
      cColor(sf::Color::Yellow),
      bExploded(false),
      imageHandle(patterns) {
    fFuse = (rand() / (float)RAND_MAX) * ROCKET_FLIGHT_MULT + ROCKET_FLIGHT_MIN;
    shape = sf::CircleShape(ROCKET_RADIUS);
    shape.setFillColor(cColor);
    fScale = (rand() / (float)RAND_MAX) * FIREWORK_MAX_SCALE + 1.0f;
    fAngle =
        atan2f((vDestination.y - vOrigin.y), (vDestination.x - vOrigin.x)) +
        1.5705;
}

void Firework::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!bExploded) {
        target.draw(shape, states);
    } else {
        for (auto item : particles) {
            target.draw(*item, states);
        }
    }
}

void Firework::update(sf::Time timeElapsed) {
    fLifetime += timeElapsed.asSeconds();
    if (fLifetime >= fFuse) {
        if (!bExploded) {
            // Explode
            float fFuseTimer =
                (rand() / (float)RAND_MAX) * FUSE_MULT + FUSE_MIN;

            sf::Image* img;
            int rnd = (rand() / (float)RAND_MAX) * imageHandle->size();
            img = (*imageHandle)[rnd];
            sf::Vector2u size = img->getSize();

            std::uint8_t r = (rand() / (float)RAND_MAX) * 128 + 127;
            std::uint8_t g = (rand() / (float)RAND_MAX) * 128 + 127;
            std::uint8_t b = (rand() / (float)RAND_MAX) * 128 + 127;
            sf::Color clr = sf::Color(r, g, b, 255);

            for (unsigned int j = 0; j < size.y; j++) {
                for (unsigned int i = 0; i < size.x; i++) {
                    sf::Color pixel = img->getPixel({i, j});
                    if (pixel == sf::Color::Black) {
                        // If black, use the random color
                        sf::Vector2f dest_offset = sf::Vector2f(
                            fScale * 10 * ((int)i - (int)((size.x - 1) / 2)),
                            fScale * 10 * ((int)j - (int)((size.y - 1) / 2)));
                        sf::Vector2f rotated_dest_offset =
                            sf::Vector2f((dest_offset.x * cosf(fAngle)) -
                                             (dest_offset.y * sinf(fAngle)),
                                         (dest_offset.x * sinf(fAngle)) +
                                             (dest_offset.y * cosf(fAngle)));
                        particles.push_back(
                            new particle(sf::Vector2f(vPosition),
                                         vPosition + rotated_dest_offset, clr,
                                         FIREWORK_PARTICLE_SIZE, fFuseTimer));
                    } else if (pixel != sf::Color::Transparent) {
                        // If different from black, use the defined color
                        sf::Vector2f dest_offset = sf::Vector2f(
                            fScale * 10 * ((int)i - (int)((size.x - 1) / 2)),
                            fScale * 10 * ((int)j - (int)((size.y - 1) / 2)));
                        sf::Vector2f rotated_dest_offset =
                            sf::Vector2f((dest_offset.x * cosf(fAngle)) -
                                             (dest_offset.y * sinf(fAngle)),
                                         (dest_offset.x * sinf(fAngle)) +
                                             (dest_offset.y * cosf(fAngle)));
                        particles.push_back(
                            new particle(sf::Vector2f(vPosition),
                                         vPosition + rotated_dest_offset, pixel,
                                         FIREWORK_PARTICLE_SIZE, fFuseTimer));
                    }
                }
            }
            bExploded = true;
        } else {
            // Already exploded: Update particles
            for (auto part : particles) {
                part->update(timeElapsed);
            }
        }
    } else {
        float factor = 1 - std::pow((1 - (fLifetime / fFuse)), EASE_POWER);
        vPosition = vOrigin + (vDestination - vOrigin) * factor;
    }
    shape.setPosition(vPosition);
}

bool Firework::isExtinguished() const {
    if (bExploded) {
        bool bExtinguished = true;
        if (particles.size() > 0) {
            for (auto item = particles.begin();
                 bExtinguished && item != particles.end(); item++) {
                /*
                 * Extinguished when ALL particles are extinguished
                 * means NOT extinguished when there is at least one particle
                 * alive
                 */
                bExtinguished &= ((*item)->bExtinguished);
            }
        }
        return bExtinguished;
    }
    return false;
}
