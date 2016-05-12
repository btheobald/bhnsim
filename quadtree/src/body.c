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
