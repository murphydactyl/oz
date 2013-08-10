#ifndef __APP__KEYBOARD__H__
#define __APP__KEYBOARD__H__

#include <map>

class Keyboard {

  public:
    typedef char keyid_t;
    static const keyid_t NUM_KEYS = 255;
    std::map<keyid_t, int> down;
    std::map<keyid_t, int> up;

    Keyboard() {
      down.clear();
      up.clear();
      for (char i = 0; i < NUM_KEYS; i++) {
        up[i] = 0;
      }
    }

    void makeDown(keyid_t theKey) {
      auto removed = up.erase(theKey);
      auto it = down.find(theKey);
      if (it != down.end()) {
        it->second++;
      } else {
        down[theKey] = 0;
      }
    }

    void makeUp(keyid_t theKey) {
      auto removed = down.erase(theKey);
      up[theKey] = 0;
    }

    bool isUp(keyid_t theKey) {
      auto it = up.find(theKey);
      return (it != up.end());
    }

    bool isDown(keyid_t theKey) {
      auto it = down.find(theKey);
      return (it != down.end());
    }

};

#endif // __APP__KEYBOARD__H__
