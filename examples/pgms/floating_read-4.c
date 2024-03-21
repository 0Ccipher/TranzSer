#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>
#include <assert.h>
void __VERIFIER_Transaction_begin();
void __VERIFIER_Transaction_end();

#define begin __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end() 


#  define N 4

atomic_intptr_t x;

static void *thread(void *arg) {
  begin;
  intptr_t thread = (intptr_t)arg;
  atomic_store(&x, thread);
  end;
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t t[N+1];
  for (intptr_t i = 1; i <= N; i++)
    pthread_create(t+i, 0, thread, (void*)i);
  begin;
  assert(atomic_load(&x) < N+1);
  end;
  for (intptr_t i = 1; i <= N; i++)
    pthread_join(t[i], 0);
  return 0;
}
