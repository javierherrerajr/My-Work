#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

class Triangle {
    public: 
        void set_base(int b);
        void set_height(int h);
        double area();
    private: 
        int base;
        int height; 
};

#endif //TRIANGLE_HPP