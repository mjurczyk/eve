#include <Picasso.h>
#include <stdlib.h>
#include <math.h>

Picasso::Picasso (unsigned int width, unsigned int height) {
  canvas_width = width;
  canvas_height = height;
  
  createCanvas(canvas_width, canvas_height);
};

void Picasso::createCanvas (unsigned int width, unsigned int height) {
  height = height / 8;
  
  canvas = (byte**) malloc(height * sizeof(byte*));
  
  if (canvas != NULL) {
    unsigned int i, j;
    
    for (i = 0; i < height; i++) {
      canvas[i] = (byte*) malloc(width * sizeof(byte));
      
      if (canvas[i] != NULL) {
        for (j = 0; j < width; j++) {
          canvas[i][j] = 0x00;
        }
      } else {
        /*
         * Handle exception once again, row couldn't be allocated.
         */  
        Serial.println("Cannot allocate canvas col");
      }
    }
    Serial.print("Canvas cols OK [");
    Serial.print(i * width * sizeof(byte));
    Serial.println(" bytes]");
    
  } else {
    /*
     * Handle exception, array could not have been allocated.
     */ 
    Serial.println("Cannot allocate canvas rows");
  }
  Serial.print("Canvas rows OK [");
  Serial.print(height * sizeof(byte*));
  Serial.println(" bytes]");
};

void Picasso::pixel (unsigned int x, unsigned int y) {
  if (x < canvas_width && x >= 0 && y < canvas_height && y >= 0) {
    canvas[y / 8][x] |= (1 << (y % 8));
  }
};

void Picasso::empty (unsigned int x, unsigned int y) {
  if (x < canvas_width && x >= 0 && y < canvas_height && y >= 0) {
    canvas[y / 8][x] &= ~(1 << (y % 8));
  }
};

void Picasso::line (unsigned int x0, unsigned int y0,
                    unsigned int x1, unsigned int y1,
                    unsigned int flags) {
  unsigned int dashCounter;
  
  if (flags & PCSS_DASHED) {
    dashCounter = 0; 
  }
  
  if (x0 == x1 && y0 == y1) {
    pixel(x0, y0);
  } else {
    if (x0 > x1) {
      utils::swapInts(&x0, &x1);
      utils::swapInts(&y0, &y1);
    }
    
    if (x0 == x1) {
      for (;y0 < y1; y0++) {
        if (flags & PCSS_DASHED) {
          if (dashCounter % 2 == 0) {
            pixel(x0, y0); 
          }
          
          dashCounter++;
        } else {
          pixel(x0, y0);
        }
      }
    } else {
      float dx = (float)x1 - (float)x0;
      float dy = (float)y1 - (float)y0;
      
      float err = 0.0;
      float derr = 0.0;
      
      int sgn = (dy > 0) - (dy < 0);
      derr = abs(dy / dx);
      
      unsigned int y = y0;
      for (;x0 <= x1; x0++) {
        if (flags & PCSS_DASHED) {
          if (dashCounter % 2 == 0) {
            pixel(x0, y); 
          }
          
          dashCounter++;
        } else {
          pixel(x0, y);
        }
        
        err += derr;
        
        while (err > 0.5) {
          y += sgn;
          
          pixel(x0, y);
          
          err = err - 1.0;
        }
      }
    }
  }
};

void Picasso::rect (unsigned int x, unsigned int y,
                    unsigned int width, unsigned int height,
                    unsigned int flags) {
  if (!(flags & PCSS_EMPTY)) {
    unsigned int emptyX = 0;
    unsigned int emptyY = 0;
    
    for(emptyX = x; emptyX < x + width; emptyX++) {
      for(emptyY = y; emptyY < y + height; emptyY++) {
       empty(emptyX, emptyY);
      }
    }
  }
  
  line(x, y, x + width, y, NULL);
  line(x + width, y, x + width, y + height, NULL);
  
  line(x, y, x, y + height, NULL);
  line(x, y + height, x + width, y + height, NULL);
  
  if (flags & PCSS_DROP_SHADOW) {
    unsigned int shadowPadding = 1;
    unsigned int dashPadding = 0;
    
    for (shadowPadding = 1; shadowPadding <= 2; shadowPadding++) {
      dashPadding = shadowPadding / 2;
      
      line(x + dashPadding + 1, y + height + shadowPadding,
           x + width + dashPadding, y + height + shadowPadding,
          PCSS_DASHED);
      
      line(x + width + shadowPadding, y + dashPadding + 1,
           x + width + shadowPadding, y + height + dashPadding + 2,
          PCSS_DASHED);
    }
  }
};

void Picasso::circle (unsigned int x, unsigned int y, unsigned int r) {
  float rads = 0;
  
  for(float da = 1; da <= 360; da++) {
    rads = da / 180 * 3.14;
    
    pixel(
      x + (unsigned int)(cos(rads) * r),
      y + (unsigned int)(sin(rads) * r)
    );
  }
};

void Picasso::clear (void) {
  for (unsigned int y = 0; y < (canvas_height / 8); y++) {
    for (unsigned int x = 0; x < canvas_width; x++) {
      canvas[y][x] = 0x00; 
    }
  }
};

byte** Picasso::getCanvas (void) {
  return canvas;
};