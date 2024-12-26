#include <Supergoon/Coroutine.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct coroutine {
  // unsigned int Id;
  void *Userdata;
  void *Userdata2;
  void (*Func)(void *, void *);
  float Waittime;
  float CurrentTime;
  bool Started;
  struct coroutine *Next;
} coroutine;
coroutine *firstCoroutine = NULL;
coroutine *lastCoroutine = NULL;

sgCoroutine sgAddCoroutine(float timeSeconds, void (*func)(void *, void *), void *userdata, void *userdata2) {
  coroutine *co = malloc(sizeof(*co));
  co->CurrentTime = 0;
  co->Next = NULL;
  co->Userdata = userdata;
  co->Userdata2 = userdata2;
  co->Func = func;
  co->Waittime = timeSeconds;
  co->Started = false;
  if (firstCoroutine == NULL) {
    firstCoroutine = lastCoroutine = co;
  } else {
    lastCoroutine->Next = co;
    lastCoroutine = co;
  }
  return co;
}

void sgUpdateCoroutines(double deltaTime) {
  coroutine *current = firstCoroutine;
  coroutine *previous = NULL;
  while (current) {
    if (current->Started) {
      current->CurrentTime += deltaTime;
    }
    if (current->CurrentTime >= current->Waittime) {
      current->Func(current->Userdata, current->Userdata2);
      coroutine *toFree = current;
      if (previous) {
        previous->Next = current->Next;
      } else {
        firstCoroutine = current->Next;
      }
      if (current == lastCoroutine) {
        lastCoroutine = previous;
      }
      current = current->Next;
      free(toFree);
    } else {
      previous = current;
      current = current->Next;
    }
  }
}

void sgStartCoroutine(sgCoroutine co) {
  coroutine *coCasted = (coroutine *)co;
  if (coCasted) {
    coCasted->Started = true;
  }
}
