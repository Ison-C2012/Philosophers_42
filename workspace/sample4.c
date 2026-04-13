#include <stdio.h>
#include <pthread.h>

int cnt = 0;
pthread_mutex_t	mutex;

void *routine(void *p)
{
	for (int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);	//lockして同時アクセスを防ぐ
		cnt++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(void)
{
	pthread_t p1, p2;
	pthread_mutex_init(&mutex, NULL);

	// 2つのスレッドで並列処理する
	pthread_create(&p1, NULL, &routine, NULL);
	pthread_create(&p2, NULL, &routine, NULL);

	// 終了するまで待つ
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	pthread_mutex_destroy(&mutex);
	printf("cnt -> %d\n", cnt);
}
