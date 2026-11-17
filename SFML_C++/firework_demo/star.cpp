#include "includes/star.hpp"

/**
 * @brief Approximates sin(v)
 *
 * @param v The argument of sine function
 * @return An approximation of sin(v)
 */
float sineApprox(const float& v) {
    return (4 * v * (3.1415 - v)) / (49.345111 - (4 * v * (3.1415 - v)));
}

/**
 * @brief Constructor
 *
 * @param position Position of the star
 * @param radius Radius of the star
 */
Star::Star(const sf::Vector2f& position, const float& radius) : fRadius(radius), vPosition(position) {
    // Create a dim and bright version of red...
    std::uint8_t red_dim = (rand() / (float)RAND_MAX) * 32;
    std::uint8_t red_bright = (rand() / (float)RAND_MAX) * 128 + 64;
    // ... and green
    std::uint8_t green_dim = (rand() / (float)RAND_MAX) * 85;
    std::uint8_t green_bright = 255;
    // Blue stays always at max, we want the star to look blue-ish
    std::uint8_t blue = 255;
    // We build the bright and dim colors
    cBrightColor = sf::Color(red_bright, green_bright, blue);
    cDimColor = sf::Color(red_dim, green_dim, blue);
    // And we set the offset of where the star status will start
    // If this offset is not randomized, all stars will blink together, looking very artificial
    fOffset = (rand() / (float)RAND_MAX) * 3.1415;
    // Initialize the sprite...
    shape = sf::CircleShape(fRadius);
    // ...And the lifetime to the offset we found earlier
    fLifeTime = fOffset;
    float sn = sineApprox(fLifeTime);
    // Here we use the sine function to find at which point of the bright->dim->bright cycle we are.
    cCurrentColor = cDimColor + sf::Color(sn * cBrightColor.r, sn * cBrightColor.g, sn * cBrightColor.b);
    // Then fill the star with the color, and position it on the screen
    shape.setFillColor(cCurrentColor);
    shape.setPosition(vPosition);
}

/**
 * @brief Draws the star
 *
 * @param target Surface to draw the star on
 * @param states Internal SFML variable
 */
void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

/**
 * @brief Updates the internal status of the star
 *
 * @param timeElapsed The time elapsed since last frame
 */
void Star::update(sf::Time timeElapsed) {
    // We update the star lifetime
    fLifeTime += timeElapsed.asSeconds();
    // If we pass "pi", we go back by "pi". This makes the lifetime cyclic, which works well for the cycling colours.
    // We're not using "pi*2" because, if we did, we could end with negative values of sin(v), which will mess up the colours.
    if (fLifeTime > 3.1415) {
        fLifeTime -= 3.1415;
    }
    // We re-approximate the sine of the lifetime
    float sn = sineApprox(fLifeTime);
    // And apply the new colour
    cCurrentColor = cDimColor + sf::Color(sn * cBrightColor.r, sn * cBrightColor.g, sn * cBrightColor.b);
    shape.setFillColor(cCurrentColor);
}
