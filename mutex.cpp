#include <iostream>
#include <thread>
#include <unistd.h>
#include <ctime>
#include <mutex>
using namespace std;
 
mutex mtx;
void worker(int id,int n){
	bool acquired_lock=false;
	int x=rand()%10;
	if(x<5){
		mtx.lock();
		acquired_lock=false;
	}
	if(acquired_lock) cout<<"Thread "<<id<<" acquired lock and is sleeping for "<<n<<" seconds \n\n";
	else cout<<"Thread "<<id<<" started and is sleeping for "<<n<<" seconds \n\n";	
	sleep(n);
	cout<<"Thread "<<id<<" woke up and exiting..\n";
	if(acquired_lock) mtx.unlock();
	mtx.unlock();
	return ;
}
int main(void){
	int n,num_thread=10;
	thread th[num_thread];
	srand(time(NULL));
	for(int i=0;i<num_thread;i++){
		n=rand()%10+1;
		th[i]=thread(worker,i+1,n);
		usleep(100);
	}
	for(int i=0;i<num_thread;i++) th[i].join();
	return 0;
}
