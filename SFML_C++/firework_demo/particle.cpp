#include "includes/particle.hpp"
#include <cmath>

// Editable constants, feel free to edit these and experiment!
const float PARTICLE_EXTINCTION_TIME = 2.0f;
const float X_DISPLACEMENT_MULT = 27;
const float X_DISPLACEMENT_OFFSET = 13;
const float DESCENT_SPEED_MULT = 50;
const float DESCENT_SPEED_OFFSET = 10;
const float EXTINGUISH_EASE_POWER = 2.0f;
const float EXTINGUISH_EASE_DIVIDER = 2.0f;
const float EXPLOSION_EASE_POWER = 2.0f;

/**
 * @brief Constructor
 *
 * @param position Position of the particle
 * @param destination Where the particle is moving towards
 * @param color Colour of the particle
 * @param radius Radius of the circle representing the particle
 * @param fuseTimer Time before the particle extinguishes
 */
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
    // Initialize the circle
    shape = sf::CircleShape(radius);
    // Fill color and set position
    shape.setFillColor(cColor);
    shape.setPosition(vPosition);
    // Calculate a random descent speed for later
    fDescentSpeed = (rand() / (float)RAND_MAX) * DESCENT_SPEED_MULT + DESCENT_SPEED_OFFSET;
}

/**
 * @brief Drawing functions
 *
 * @param target Surface to draw the particle on
 * @param states Internal SFML variable
 */
void particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!bExtinguished) {
        // We draw the particle only if it's not extinguished, to save on resources.
        target.draw(shape, states);
    }
}

/**
 * @brief Internal Status update for the particle
 *
 * @param timeElapsed The amount of time passed from last frame
 */
void particle::update(sf::Time timeElapsed) {
    // Update the particle lifetime
    fLifetime += timeElapsed.asSeconds();
    // If the particle is extinguished (over its lifetime plus the time for the fadeout)...
    if (fLifetime >= fFuse + PARTICLE_EXTINCTION_TIME) {
        // Set the variable Extinguished to true
        bExtinguished = true;
    } else if (fLifetime >= fFuse) {
        // We passed the particle lifetime and we are extinguishing...
        // Use an easing function to darken the colours
        float factor = 1 - std::pow((1 - ((fLifetime - fFuse) / EXTINGUISH_EASE_DIVIDER)), EXTINGUISH_EASE_POWER);
        // Separate for red-green-blue channels
        std::uint8_t red = cColor.r + ((-cColor.r) * factor);
        std::uint8_t green = cColor.g + ((-cColor.g) * factor);
        std::uint8_t blue = cColor.b + ((-cColor.b) * factor);
        // Fill the particle with the new colour
        shape.setFillColor(sf::Color(red, green, blue));
        // Use a random x displacement to make the particles look like they're kind-of-floating as they die
        float xDisplacement = (rand() / (float)RAND_MAX) * X_DISPLACEMENT_MULT - X_DISPLACEMENT_OFFSET;
        // Displace the x position by such amount
        vPosition += sf::Vector2f(xDisplacement, fDescentSpeed) * timeElapsed.asSeconds();
    } else {
        // We're still exploding outwards...
        // Use an easing function to define how fast the particles are approaching the destination
        // Try setting this to only the integer 1 and look at what happens!
        float factor = 1 - std::pow((1 - (fLifetime / fFuse)), EXPLOSION_EASE_POWER);
        // Set the position of the particles
        vPosition = vStartPosition + (vDestination - vStartPosition) * factor;
    }
    // Set the particle position.
    shape.setPosition(vPosition);
}
