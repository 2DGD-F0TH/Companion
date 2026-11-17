#ifndef STAR_H
#define STAR_H

#include <SFML/Graphics.hpp>

/**
 * @class Star
 * @brief Defines a single star in the background
 *
 */
class Star : public sf::Drawable {
   private:
    sf::CircleShape shape;    //!< Sprite representing the star (circle)
    float fRadius;            //!< Radius of the star (since it's a circle)
    sf::Color cBrightColor;   //!< Color of the star when at max brightness
    sf::Color cDimColor;      //!< Color of the star when at min brightness
    sf::Color cCurrentColor;  //!< Current color of the star
    float fOffset;           //!< Offset used to avoid all stars starting at the same status (they would be all flashing together otherwise)
    float fLifeTime;         //!< How long the star has been alive, cicles between 0 and 3.1415 (pi)
    sf::Vector2f vPosition;  //!< Position of the star in the background

   public:
    // Constructor
    Star(const sf::Vector2f& position = sf::Vector2f(0, 0), const float& radius = 2.0f);
    // Virtual Destructor
    virtual ~Star() = default;
    // Drawing function
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    // State update
    void update(sf::Time timeElapsed);
};

#endif /* STAR_H */
