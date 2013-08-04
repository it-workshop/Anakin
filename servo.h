#ifndef ANAKIN_SERVO_H_
#define ANAKIN_SERVO_H_

class Servo {
 public:
  Servo():
    reg_(0),
    pin_(0) {}
  Servo(volatile unsigned char * reg, int pin)
    : reg_(reg),
      pin_(pin),
      alpha_(0),
      delta_(50),
      pulse_(false),
      timeout_(0) {}

  // rotation speed in 0.1 of degrees per 20uS
  void set_speed(unsigned int v) { delta_ = v; }
  int speed() const { return delta_; }

  // angle in 0.1 of degrees.
  void set_angle(unsigned int v) { angle_ = alpha_ = v; }
  int angle() const { return alpha_; }

  // Set angle, using speed.
  void MoveTo(unsigned int angle, unsigned int delta = 0) {
    int old_delta = delta_;
    delta_ = delta == 0 ? delta_ : delta;
    if (pulse_)
      timeout_ += (pulse_ ? 1 : -1) * (delta_ - old_delta);
    angle_ = angle;
  }

  unsigned int Dispatch(unsigned int time_delta) {
    if (time_delta >= timeout_) {
      if (pulse_) {
        *reg_ &= ~(1 << pin_);
        timeout_ +=
          kSendIntervaluSeconds - alpha_ - kMinPulseuSeconds - time_delta;
      } else {
        *reg_ |= (1 << pin_);
        timeout_ += kMinPulseuSeconds + alpha_ - time_delta;
        if (angle_ > alpha_)
          alpha_ += (angle_ - alpha_ > delta_) ? delta_ : (angle_ - alpha_);
        else if (angle_ < alpha_)
          alpha_ -= (alpha_ - angle_ > delta_) ? delta_ : (alpha_ - angle_);
      }
      pulse_ = !pulse_;
      return timeout_;
    }
    return timeout_ -= time_delta;
  }

  template <class iterator>
  static unsigned int DispatchServos(iterator begin,
                               iterator end,
                               unsigned int time_delta) {
    unsigned int min = kSendIntervaluSeconds;
    for (iterator it = begin; it != end; ++it ) {
      unsigned int delta = it->Dispatch(time_delta);
      min = min < delta ? min : delta;
    }
    return min;
  }

 private:
  static const unsigned int kMaxdDegrees;
  static const unsigned int kMinPulseuSeconds;
  static const unsigned int kMaxPulseuSeconds;
  static const unsigned int kSendIntervaluSeconds;
  volatile unsigned char * reg_;
  unsigned int pin_;
  unsigned int angle_;
  unsigned int alpha_;
  unsigned int delta_;
  bool pulse_;
  unsigned int timeout_;
};

#endif  // ANAKIN_SERVO_H_
