#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        // exit(1);
        return 1;
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        // exit(1);
        return 1;
    }

    s = shm;

    int red = 0;
    int green = 0;
    int blue = 0;
    sprintf(s, " RGB(%3d %3d %3d)", red, green, blue);

    while (*shm != '*') sleep(1);

    // exit(0);
    return 1;
}
