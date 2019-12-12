#ifndef BASECOMPONENT_HH
#define BASECOMPONENT_HH

class BaseComponent{
    protected:
        int price;
    public:
        BaseComponent(){};
        BaseComponent(int price);
        float get_total_price();
        float get_own_score();
        float get_total_score();
};

#endif