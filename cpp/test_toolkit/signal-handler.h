//
// Created by metopa on 22.02.2016.
//

#ifndef SOLUTIONS_SIGNALHANDLER_H
#define SOLUTIONS_SIGNALHANDLER_H

#include <csignal>
#include <iostream>

typedef void (*sig_handler_func)(int);

template<int SigNum, class T>
class SignalHandler {
public:
    SignalHandler(T *functor) {
      functor_ = functor;
      old_callback_ = std::signal(SigNum, Callback);
    }
    ~SignalHandler() {
      functor_ = nullptr;
      std::signal(SigNum, old_callback_);
    }
private:
    static void Callback(int signum) {
      if (functor_)
        (*functor_)(signum);
    }
    static T *functor_;
    sig_handler_func old_callback_;
};

template<int SigNum, class T> T *SignalHandler<SigNum, T>::functor_ = nullptr;

template<int SigNum, class T>
SignalHandler<SigNum, T> SetSignalHandler(T *functor) {
  return SignalHandler<SigNum, T>(functor);
};


#endif //SOLUTIONS_SIGNALHANDLER_H
