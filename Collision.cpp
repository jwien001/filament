/*
 * File:   collision.cpp
 * Author: Nick
 *
 * Created on 30 January 2009, 11:02
 */
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include <math.h>

Collision::Collision() {
}

Collision::~Collision() {
}

sf::Vector2f Collision::RotatePoint(const sf::Vector2f& Point, float Angle) {
    Angle = Angle * RADIANS_PER_DEGREE;
    sf::Vector2f RotatedPoint;
    RotatedPoint.x = Point.x * cos(Angle) + Point.y * sin(Angle);
    RotatedPoint.y = -Point.x * sin(Angle) + Point.y * cos(Angle);
    return RotatedPoint;
}

bool Collision::CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
    //Simplest circle test possible
    //Distance between points <= sum of radius

    float Radius1 = (Object1.getGlobalBounds().width + Object1.getGlobalBounds().height) / 4;
    float Radius2 = (Object2.getGlobalBounds().width + Object2.getGlobalBounds().height) / 4;
    float xd = Object1.getPosition().x - Object2.getPosition().x;
    float yd = Object1.getPosition().y - Object2.getPosition().y;

    return sqrt(xd * xd + yd * yd) <= Radius1 + Radius2;
}

//From Rotated Rectangles Collision Detection, Oren Becker, 2001

bool Collision::BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {

    sf::Vector2f A, B, C, BL, TR;
    sf::FloatRect Bounds1 = Object1.getGlobalBounds();
    sf::FloatRect Bounds2 = Object2.getGlobalBounds();
    sf::Vector2f HalfSize1(Bounds1.width, Bounds1.height);
    sf::Vector2f HalfSize2(Bounds2.width, Bounds2.height);

    //For somereason the Vector2d divide by operator
    //was misbehaving
    //Doing it manually
    HalfSize1.x /= 2;
    HalfSize1.y /= 2;
    HalfSize2.x /= 2;
    HalfSize2.y /= 2;
    //Get the Angle we're working on
    float Angle = Object1.getRotation() - Object2.getRotation();
    float CosA = cos(Angle * RADIANS_PER_DEGREE);
    float SinA = sin(Angle * RADIANS_PER_DEGREE);

    float t, x, a, dx, ext1, ext2;

    //Normalise the Center of Object2 so its axis aligned an represented in
    //relation to Object 1
    C = Object2.getPosition();

    C -= Object1.getPosition();

    C = RotatePoint(C, Object2.getRotation());

    //Get the Corners
    BL = TR = C;
    BL -= HalfSize2;
    TR += HalfSize2;

    //Calculate the vertices of the rotate Rect
    A.x = -HalfSize1.y*SinA;
    B.x = A.x;
    t = HalfSize1.x*CosA;
    A.x += t;
    B.x -= t;

    A.y = HalfSize1.y*CosA;
    B.y = A.y;
    t = HalfSize1.x*SinA;
    A.y += t;
    B.y -= t;

    t = SinA * CosA;

    // verify that A is vertical min/max, B is horizontal min/max
    if (t < 0) {
        t = A.x;
        A.x = B.x;
        B.x = t;
        t = A.y;
        A.y = B.y;
        B.y = t;
    }

    // verify that B is horizontal minimum (leftest-vertex)
    if (SinA < 0) {
        B.x = -B.x;
        B.y = -B.y;
    }

    // if rr2(ma) isn't in the horizontal range of
    // colliding with rr1(r), collision is impossible
    if (B.x > TR.x || B.x > -BL.x) return false;

    // if rr1(r) is axis-aligned, vertical min/max are easy to get
    if (t == 0) {
        ext1 = A.y;
        ext2 = -ext1;
    }// else, find vertical min/max in the range [BL.x, TR.x]
    else {
        x = BL.x - A.x;
        a = TR.x - A.x;
        ext1 = A.y;
        // if the first vertical min/max isn't in (BL.x, TR.x), then
        // find the vertical min/max on BL.x or on TR.x
        if (a * x > 0) {
            dx = A.x;
            if (x < 0) {
                dx -= B.x;
                ext1 -= B.y;
                x = a;
            } else {
                dx += B.x;
                ext1 += B.y;
            }
            ext1 *= x;
            ext1 /= dx;
            ext1 += A.y;
        }

        x = BL.x + A.x;
        a = TR.x + A.x;
        ext2 = -A.y;
        // if the second vertical min/max isn't in (BL.x, TR.x), then
        // find the local vertical min/max on BL.x or on TR.x
        if (a * x > 0) {
            dx = -A.x;
            if (x < 0) {
                dx -= B.x;
                ext2 -= B.y;
                x = a;
            } else {
                dx += B.x;
                ext2 += B.y;
            }
            ext2 *= x;
            ext2 /= dx;
            ext2 -= A.y;
        }
    }

    // check whether rr2(ma) is in the vertical range of colliding with rr1(r)
    // (for the horizontal range of rr2)
    return !((ext1 < BL.y && ext2 < BL.y) ||
            (ext1 > TR.y && ext2 > TR.y));

}
