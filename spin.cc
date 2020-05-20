#include <napi.h>
#include <thread>

class Spinner {
  public:
    bool spin;
    Spinner(bool x) {
       spin = x;
    }
    void stop() {
	spin = false;
    }
   void start() {
       spin = true;
    }
    bool spinning() { 
       return spin;
    }
};

Spinner mySpin(false);



void advance_cursor() {
  static int pos=0;
  char cursor[4]={'/','-','\\','|'};
  printf("%c\b", cursor[pos]);
  fflush(stdout);
  pos = (pos+1) % 4;
}

void loopThread() {
 for(;;) {
     if(mySpin.spinning() == true) {
	   advance_cursor();
       } else {
          break;
       }
   }
}

void Stop(const Napi::CallbackInfo& info) {
  mySpin.stop();
}	

void Start(const Napi::CallbackInfo& info) {
   mySpin.start();

std::thread fooThread(loopThread);
  fooThread.join();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("stop", Napi::Function::New(env, Stop));
  exports.Set( "start", Napi::Function::New(env, Start));
  return exports;
}

NODE_API_MODULE(spin, Init)
