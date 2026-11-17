#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

/**
 * @class particle
 * @brief Defines a firework particle
 *
 */
class particle : public sf::Drawable {
    // The double "public" labelling is necessary for initialization ordering
   public:
    // Variables that can be read/changed from outside
    bool bExtinguished;   //!< Whether the particle is extinguished
    float fDescentSpeed;  //!< The speed the particle is falling towards the bottom of the screen
   private:
    sf::Vector2f vPosition;       //!< Position of the particle
    float fLifetime;              //!< How long a particle has been alive
    float fFuse;                  //!< How long a particle can last
    sf::Color cColor;             //!< Color of the particle
    sf::CircleShape shape;        //!< Sprite of the particle (circle)
    sf::Vector2f vDestination;    //!< Destination (x,y) the particle is moving towards
    sf::Vector2f vStartPosition;  //!< Starting position (x,y) of the particle

   public:
    // Constructor
    particle(const sf::Vector2f& position = sf::Vector2f(0, 0),
             const sf::Vector2f& destination = sf::Vector2f(0, 0),
             const sf::Color& color = sf::Color::White,
             const float& radius = 5.0f,
             const float& fuseTimer = 2.0f);
    // Virtual Destructor
    virtual ~particle() = default;
    // Drawing function
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    // Status update Function
    void update(sf::Time timeElapsed);
};
#endif /* end of include guard: PARTICLE_HPP */
