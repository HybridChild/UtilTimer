#pragma once
#include <functional>

class UtilTimer
{
public:
  UtilTimer(uint32_t timeout, bool autoReset, std::function<void()> callback)
    : _timeout(timeout)
    , _autoReset(autoReset)
    , _callback(callback)
    , _counter(0)
  {}

  void start() { _counter = 1; }
  void stop() { _counter = 0; }
  bool isRunning() const { return _counter > 0; }
  bool isExpired() const { return _counter > _timeout; }

  void setTimeout(uint32_t timeout_ms) { _timeout = timeout_ms; }
  void setAutoReset(bool autoReset) { _autoReset = autoReset; }
  uint32_t getCounter() const { return _counter; }
  uint32_t getTimeout() const { return _timeout; }

  void service(uint32_t timePassed)
  {
    if (isRunning())
    {
      _counter += timePassed;

      if (isExpired())
      {
        if (_callback) { _callback(); }

        if (_autoReset) { start(); }
        else { stop(); }
      }
    }
  }

private:
  uint32_t _timeout;
  bool _autoReset;
  std::function<void()> _callback;
  uint32_t _counter;
};
