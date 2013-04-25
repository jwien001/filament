#ifndef BEAM_H
#define BEAM_H

#include "Player.h"

class Beam : public ILevelObject, public ICollidable
{
    sf::RectangleShape rect;
    int numBlocks;
    int traceNum;

    public:
        static const sf::Mouse::Button BUTTON;

        Beam(Player* player);

        void update(Level& level, sf::Time delta) override;
        void move(float count);

        const sf::Vector2f& getPosition() const override {
            return rect.getPosition();
        }

        void setPosition(const sf::Vector2f& pos) override {
            rect.setPosition(pos);
        }

        sf::FloatRect getCollisionBox() const override {
            return rect.getGlobalBounds();
        }

        const sf::Color& getColor() const override {
            return rect.getOutlineColor();
        }

        const sf::Vector2f& getSize() const {
            return rect.getSize();
        }

        void setRotation(float angle) {
            rect.setRotation(angle);
        }

        void addBlocks(int num) {
            numBlocks += num;
        }

        int removeBlocks() {
            int num = numBlocks;
            numBlocks = 0;
            return num;
        }

        bool isCollidingWith(ICollidable& other) override {
            if (getCollisionBox().intersects(other.getCollisionBox())) {
                //Bounding box intersection is inaccurate, so use trace to double check
                int t = trace(other);

                //If a smaller trace number was already calculated, we should not be colliding past that
                if (t >=0 && t <= traceNum) {
                    traceNum = t;
                    return true;
                }
            }
            return false;
        };

        /**
         * Perform ray casting along the beam, returning the length at which the first collision is detected.
         */
        int trace(ICollidable& other);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(rect);
        };
};

#endif // BEAM_H
