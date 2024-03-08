
extern int _system_time;
void sleep(int ms){
  int init = _system_time;
  while (_system_time - init < ms){ 
    /* waiting */
  }
  return;
}

void play_note(int ch, int inst, int note, int vel, int dur);


const int insts[11] = {0,30,0,30,0,34,0,0,0,0,30};
int notas[13][6] = {{720, 840, 4, 5, 40, 95},
                    {960, 1080, 4, 5, 43, 95},
                    {1320, 1440, 4, 5, 40, 95},
                    {1680, 1920, 4, 5, 38, 95},
                    {1920, 2880, 4, 5, 36, 95},
                    {2880, 3840, 4, 5, 35, 95},
                    {3840, 4560, 4, 5, 40, 95},
                    {4560, 4680, 4, 5, 40, 95},
                    {4800, 4920, 4, 5, 43, 95},
                    {5160, 5280, 4, 5, 40, 95},
                    {5520, 5760, 4, 5, 38, 95},
                    {5760, 6720, 4, 5, 36, 95},
                    {6720, 7680, 4, 5, 35, 95}};

void main(){
  int bpm = 124;
  int ticks = 960;
  int last_ini = 0;

  for (int i = 0; i < 13; i++){
    notas[i][0] = (notas[i][0]*6000)/(bpm*(ticks/10));
    notas[i][1] = (notas[i][1]*6000)/(bpm*(ticks/10));
  }
  

  while (1){
    last_ini = 0;
    for (int i = 0; i < 13; i++){
      sleep(notas[i][0] - last_ini); 
      last_ini = notas[i][0];
      play_note(notas[i][3], insts[notas[i][3]], notas[i][4], notas[i][5], notas[i][1] - notas[i][0]);
    }
  }
  
  return;
}
