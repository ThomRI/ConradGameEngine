#ifndef SCOPE_H_INCLUDED
#define SCOPE_H_INCLUDED

#define GLM_ENABLE_EXPERIMENTAL

/* Defines a byte offset from an index offset */
#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + offset)
#endif

/* Defines for VertexAttribPointer IDs */
#define VERTEX_BUFFER   0
#define COLOR_BUFFER    1
#define TEX_BUFFER      2

/* 2D Grid manipulations (returns an index from (x, y) coordinates in a 2D grid) */
#ifndef GRID_2D_INDEX
    #define GRID_2D_INDEX(x, y, w) (y * w + x)
#endif

#endif // SCOPE_H_INCLUDED
