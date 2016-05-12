typedef struct {
  float m;
  float xP, yP;
  float xV, yV;
  float xA, yA;
} body;

// Allocate memory for body and initialise
body* createBody(float p_m, float p_xP, float p_yP, float p_xV, float p_yV);
