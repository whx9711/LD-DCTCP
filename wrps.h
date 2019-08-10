 /* Strict Priority Queueing (SP)
 * 
 * Variables:
 * queue_num_: number of Class of Service (CoS) queues
 * thresh_: ECN marking threshold
 * mean_pktsize_: configured mean packet size in bytes
 * marking_scheme_: Disable ECN (0), Per-queue ECN (1) and Per-port ECN (2)
 */

#ifndef ns_wrps_h
#define ns_wrps_h



#define DISABLE_ECN 0
#define PER_QUEUE_ECN 1
#define PER_PORT_ECN 2

#include <string.h>
#include "queue.h"
#include "config.h"

class wrps : public Queue {
	public:
             wrps()
		{
			queue_num_ = 1;
			marking_thresh_ = 65;
					
	            	queue_length_ = 0;      
			cur_queue_ = 0;

		
			//Bind variables
			bind("queue_num_", &queue_num_);
			bind("q_weight_0_",&q_weight[0]);
			bind("q_weight_1_",&q_weight[1]);
			bind("q_weight_2_",&q_weight[2]);
			bind("q_weight_3_",&q_weight[3]);
			bind("q_weight_4_",&q_weight[4]);
			bind("q_weight_5_",&q_weight[5]);
			bind("q_weight_6_",&q_weight[6]);
			bind("q_weight_7_",&q_weight[7]);
			                     
                       for(int i = 0; i <= queue_num_; i++)
                       {
                             q_weight_counter[i] = q_weight[i];
                       }                        
			//Init queues
			q_=new PacketQueue*[queue_num_];
			for(int i=0; i <= queue_num_; i++)
			{
				q_[i]=new PacketQueue;
			}
		}

		~wrps()
		{
			for(int i=0; i <= queue_num_; i++)
			{
				delete q_[i];
			}
			delete[] q_;
		}

	protected:
		void enque(Packet*);	
		Packet* deque();       

                PacketQueue **q_;		// multi-FIFO queues
		
		int marking_thresh_;	
		int queue_num_;			// number of queues.
	
		void reset_queue_weight();
		int queue_length_;       //
		int q_weight[8];
		int q_weight_counter[8];
		int cur_queue_;

	
};

#endif


