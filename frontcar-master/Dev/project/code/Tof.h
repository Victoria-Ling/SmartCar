#ifndef TOF_H_
#define TOF_H_

void duan_or_po(void);
void barrier(void);

extern int ramp_time;
extern uint16 distance_mm[4];
extern uint16 distance_pingjun;
extern int8 hengduan;
extern int8 finish;
extern int8 barrier_type[6];
extern int8 cout_finish;
extern float obstacle_p, obstacle_d;//65
extern int8 angle_want;
extern int8 obstacle_error[2];

#endif /* TOF_H_ */
