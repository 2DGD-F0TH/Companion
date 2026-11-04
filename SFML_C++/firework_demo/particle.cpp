#include "includes/particle.hpp"
#include <cmath>

const float PARTICLE_EXTINCTION_TIME = 2.0f;
const float X_DISPLACEMENT_MULT = 27;
const float X_DISPLACEMENT_OFFSET = 13;
const float DESCENT_SPEED_MULT = 50;
const float DESCENT_SPEED_OFFSET = 10;
const float EXTINGUISH_EASE_POWER = 2.0f;
const float EXTINGUISH_EASE_DIVIDER = 2.0f;
const float EXPLOSION_EASE_POWER = 2.0f;

particle::particle(const sf::Vector2f& position,
                   const sf::Vector2f& destination,
                   const sf::Color& color,
                   const float& radius,
                   const float& fuseTimer)
    : bExtinguished(false),
      vPosition(position),
      fLifetime(0.0f),
      fFuse(fuseTimer),
      cColor(color),
      vDestination(destination),
      vStartPosition(position) {
    shape = sf::CircleShape(radius);
    shape.setFillColor(cColor);
    shape.setPosition(vPosition);
    fDescentSpeed =
        (rand() / (float)RAND_MAX) * DESCENT_SPEED_MULT + DESCENT_SPEED_OFFSET;
}

void particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!bExtinguished) {
        target.draw(shape, states);
    }
}

void particle::update(sf::Time timeElapsed) {
    fLifetime += timeElapsed.asSeconds();
    if (fLifetime >= fFuse + PARTICLE_EXTINCTION_TIME) {
        // Extinguished
        bExtinguished = true;
    } else if (fLifetime >= fFuse) {
        // Extinguishing
        float factor =
            1 - std::pow((1 - ((fLifetime - fFuse) / EXTINGUISH_EASE_DIVIDER)),
                         EXTINGUISH_EASE_POWER);
        std::uint8_t red = cColor.r + ((-cColor.r) * factor);
        std::uint8_t green = cColor.g + ((-cColor.g) * factor);
        std::uint8_t blue = cColor.b + ((-cColor.b) * factor);
        shape.setFillColor(sf::Color(red, green, blue));
        float xDisplacement = (rand() / (float)RAND_MAX) * X_DISPLACEMENT_MULT -
                              X_DISPLACEMENT_OFFSET;
        vPosition += sf::Vector2f(xDisplacement, fDescentSpeed) *
                     timeElapsed.asSeconds();
    } else {
        // Exploding
        float factor =
            1 - std::pow((1 - (fLifetime / fFuse)), EXPLOSION_EASE_POWER);
        vPosition = vStartPosition + (vDestination - vStartPosition) * factor;
    }
    shape.setPosition(vPosition);
}
