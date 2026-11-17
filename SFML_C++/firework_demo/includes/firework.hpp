#ifndef FIREWORK_H
#define FIREWORK_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include "particle.hpp"

/**
 * @class Firework
 * @brief Defines a firework rocket, along with its particles
 *
 */
class Firework : public sf::Drawable {
   private:
    sf::Vector2f vDestination;             //!< Destination (x,y) the rocket is flying towards
    sf::Vector2f vOrigin;                  //!< (x,y) Origin from where the rocket starts
    sf::Vector2f vPosition;                //!< (x,y) Current position of the rocket
    float fLifetime;                       //!< How long the rocket has been flying for
    float fFuse;                           //!< Time to wait before the rocket explodes
    sf::CircleShape shape;                 //!< The sprite representing the rocket (circle)
    sf::Color cColor;                      //!< The color of the rocket
    bool bExploded;                        //!< Defines if a rocket has exploded already
    std::list<particle*> particles;        //!< List of all the particles shot by a rocket when exploded
    float fScale;                          //!< Scaling factor for the particles
    std::vector<sf::Image*>* imageHandle;  //!< Handle for the image pattern
    float fAngle;                          //!< Angle at which the rocket is shot

   public:
    // Constructor
    Firework(const sf::Vector2f& origin, const sf::Vector2f& destination, std::vector<sf::Image*>* patterns);
    // Drawing function
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    // Status update function
    void update(sf::Time timeElapsed);
    // Virtual destructor
    virtual ~Firework() = default;
    // Getter for the "extinguished" status
    bool isExtinguished() const;
};

#endif /* FIREWORK_H */
