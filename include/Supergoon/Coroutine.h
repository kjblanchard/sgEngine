#pragma once
#ifdef __cplusplus
extern "C" {
#endif
typedef void *sgCoroutine;
sgCoroutine sgAddCoroutine(float timeSeconds, void (*func)(void *), void *userdata);
void sgUpdateCoroutines(double deltaTIme);
void sgStartCoroutine(sgCoroutine co);
#ifdef __cplusplus
}
#endif
