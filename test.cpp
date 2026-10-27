import std;

class Rectangle {
private:
    double length;
    double width;
public:
    Rectangle(double length, double width): 
        length{length}, width{width} {}

    virtual void display() const {
        std::println("Rectangle[length={}, width={}]", length, width);
    }
};

class Box: public Rectangle {
private:
    double height;
public:
    Box(double length, double width, double height): 
        Rectangle(length, width), height{height} {}

    void display() const override {
        // Invoke parent display() method.
        Rectangle::display();
        std::println("Box[length={}, width={}, height={}]", length, width, height);
    }
};

int main() {
    Box box(67, 67, 67);
    box.display();
}
