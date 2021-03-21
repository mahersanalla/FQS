#include "QOSInterface/interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 1024



//size_t sampleForSeconds(float delay_in_secs, char* dev_name, size_t pid, FILE* fptr);
//void printBuf(size_t buf[], FILE* fptr);

int main(int argc, char* argv[])
{ 
	if (argc != 3)
	{
		// Device name - pid number
		printf("Must supply the following parametres in order: Device name - pid number  \n");
		return -1;
	}
//	char** dummy_ptr;	
	setNetDevice(argv[1], strtol(argv[2], NULL, 10));	
	m_stats s={0,0,0,0,0};
	getQueueStats(&s);	
   	printf("Stats are: QLen = %zu, drops=%zu, BLog=%zu, requeues=%zu, overlimits=%zu \n",s.qlen,s.drops,s.backlog,s.requeues,s.overlimits);
        return 0;
}

/*
 * Samples the Qdisc of the specified <dev_name> for <time> amount of seconds, 
 * under the net that is defined over the given <pid>.
 * Return - the number of times that the Qdisc have been sampled.
 */
/*size_t sampleForSeconds(float delay_in_secs, char* dev_name, size_t pid,FILE* fptr)
{
    time_t start_time;
    time_t now;
    float elapsed_time;
    setNetDevice(dev_name, pid);
    size_t buf[BUF_SIZE];
    size_t sample_cnt = 0;
    size_t buf_idx = 0;
    time(&start_time);
    while (elapsed_time < delay_in_secs) {
		buf[buf_idx++]=printQueueSize();
		++sample_cnt;
		if (buf_idx >= BUF_SIZE)
		{
			printBuf(buf,fptr);
			buf_idx = 0; //-- empty buffer
		}
        now = time(NULL);
        elapsed_time = difftime(now, start_time);
    }
    return sample_cnt;
}

void printBuf(size_t buf[],FILE* fptr)
{
	int i = 0 , buffer_count=0;
	size_t CHUNK_SIZE=BUF_SIZE * (sizeof(size_t) + 1 );
	char file_buffer[CHUNK_SIZE];
	while( i < BUF_SIZE )
	{
	 	buffer_count+=sprintf( &file_buffer[buffer_count], "%ld\n", buf[i++] ) ;
	}
	
	fwrite(file_buffer,sizeof(char),buffer_count,fptr);
}
*/
