#include <stdio.h>
#include <stdbool.h>
#include <linux/gen_stats.h>
typedef struct{
	size_t	qlen;
	size_t	backlog;
	size_t	drops;
	size_t	requeues;
	size_t	overlimits;
}m_stats;

void setNetDevice(char* net_dev_name, size_t pid){
	if(!net_dev_name) return;
	//-- Trigger QOS module <set device> attribute.
	FILE *fpw;
	fpw = fopen("/sys/kernel/QOSInfo/setDevice","w");
	if(fpw == NULL)
	{
		fprintf(stderr, "Error, falied Triggering <set device> attribute\n");
		return;             
	}
	fprintf(fpw,"%s %zu", net_dev_name, pid);
	fclose(fpw);
	return;
}

int getQueueStats(m_stats* s){
	FILE *fp1 = NULL;
	//-- Trigger QOS module <get device queue size> attribute.
	fp1= fopen ("/sys/kernel/QOSInfo/getQueueStats", "r");
	if(!fp1)
	{	
		fprintf(stderr, "Error, falied Triggering <get queue stats> attribute\n");
		return 0;
	}
	while( fscanf(fp1, "%zu %zu %zu %zu %zu", &s->qlen,&s->backlog,&s->drops,&s->requeues,&s->overlimits) == 5 ) { }
	fclose(fp1);
	return 1;
}
