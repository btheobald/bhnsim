#include "body.h"
#include <stdlib.h>

// Allocate memory for body and initialise
body* createBody(float p_m, float p_xP, float p_yP, float p_xV, float p_yV) {
  // Allocate memory for body
  body* tempBody = malloc(sizeof(body));

  // Initialise
  tempBody->m = p_m;
  tempBody->xP = p_xP;
  tempBody->yP = p_yP;
  tempBody->xV = p_xV;
  tempBody->yV = p_yV;
  tempBody->xA = 0;
  tempBody->yA = 0;

  // Return body pointer
  return tempBody;
}

// Sum body to current body
void sumBody(body* target, body* add) {
  float xT = 0, yT = 0;
  // Add initial position and weight.
  xT = (target->xP * target->m);
  yT = (target->yP * target->m);
  // Add Weighted added body position
  xT = xT + (add->xP * add->m);
  yT = yT + (add->yP * add->m);
  // Calcuate total mass
  target->m = target->m + add->m;
  // Calculat=e actual weighted position
  target->xP = xT / target->m;
  target->yP = yT / target->m;
}
