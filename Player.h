#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Entity.h"
#include "Block.h"
#include "TextureManager.h"

class Beam;

struct ColorHash
{
    std::size_t operator()(const sf::Color c) const {
        return (c.r << 16) | (c.g << 8) | c.b;
    }
};

class Player : public Entity
{
    /* These constants control the Player's movement */
    //SPEED is the horizontall move speed
    static const float SPEED;
    //JUMP controls the initial jump speed
    static const float JUMP;
    //GRAVITY determines how fast the Player falls
    static const float GRAVITY;

    static std::vector<sf::Color> colorList;
    static std::unordered_map<sf::Color, std::string, ColorHash> texMap;

    std::unordered_map<sf::Color, int, ColorHash> inventory;

    sf::Vector2f oldPosition;
    int colorIndex;
    bool airborne;
    bool phasing;
    std::shared_ptr<Beam> beam;

    public:
        Player();

        void update(Level& level, sf::Time delta) override;
        void drawUI(sf::RenderTarget& target, sf::Font& font, sf::View& view);
        void handleEvent(sf::Event& event, Level& level);

        void setAirborne(bool a) {
            airborne = a;
        }

        const sf::Vector2f& getOldPosition() const {
            return oldPosition;
        }

        void setOldPosition(const sf::Vector2f& oldPos) {
            oldPosition = oldPos;
        }

        const sf::Vector2f& getCenter() const {
            sf::FloatRect box = sprite.getGlobalBounds();
            return sf::Vector2f(box.left + box.width/2, box.top + box.height/2);
        }

        const sf::Color& getColor() const override {
            return colorList[colorIndex];
        }

        bool isCollidingWith(ICollidable& other) override {
            if (getCollisionBox().intersects(other.getCollisionBox())) {
                if (getColor() != other.getColor())
                    return true;

                //Player is overlapping a block of the same color
                phasing = true;
            }
            return false;
        };

    private:
        void nextColor() {
            if (++colorIndex >= colorList.size())
                colorIndex = 0;
            sf::Texture* tex = texManager.getResource(texMap[colorList[colorIndex]]);
            sprite.setTexture(*tex);
        }
};

#endif // PLAYER_H
