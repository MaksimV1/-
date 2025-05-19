#pragma once

namespace SnakeGame {
    public ref class Point {
    public:
        int X;
        int Y;

        Point(int x, int y) {
            X = x;
            Y = y;
        }

        Point^ Clone() {
            return gcnew Point(X, Y);
        }
    };
}