#include "Pedals.hpp"

Pedals::Pedals():
throttle_(THROTTLE_PIN),
brake_(BRAKE_PIN)
{}

Pedals::~Pedals() {}
