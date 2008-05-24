/*
 *  KikiCharacter.cpp
 *  kiki
 */

#include "KikiCharacter.h"
#include "KikiText.h"

#include <KMatrix.h>
#include <KDisplayTools.h>
#include <KConsole.h>

#define K_INCLUDE_GLU
#include "KIncludeTools.h"

// __________________________________________________________________________________________________
typedef struct {
  GLdouble x;
  GLdouble y;
  GLdouble z;
} KikiCharCoords;

// __________________________________________________________________________________________________
static KikiCharCoords KikiCharacterData[][3][30] = {

    {{	{0,0}, {2,0}, {2,2}, {0,2}, {-1}}, 					// !
        {{0,3}, {2,3}, {2,8}, {0,8}, {-1}}, {{-1}}}, 
    {{	{0,6}, {1,6}, {2,7}, {2,6}, {3,6}, {4,7}, {4,8}, {3,8}, {2,7}, {2,8},	// "
        {1,8}, {0,7}, {-1}}, {{-1}}, {{-1}}},
    {{	{1,0}, {3,0}, {3,1}, {4,1}, {4,0}, {6,0}, {6,1}, {7,1}, {7,3}, {6,3},	// #
        {6,4}, {7,4}, {7,6}, {6,6}, {6,7}, {4,7}, {4,6}, {3,6}, {3,7}, {1,7}, 
        {1,6}, {0,6}, {0,4}, {1,4}, {1,3}, {0,3}, {0,1}, {1,1}, {-1}}, 
        {{3,3}, {3,4}, {4,4}, {4,3}, {-1}}, {{-1}}},
    {{	{1,0}, {5,0}, {6,1}, {6,4}, {5,5}, {4,5}, {4,6}, {6,6}, {6,7}, {5,8},	// $ 
        {1,8}, {0,7}, {0,4}, {1,3}, {2,3}, {2,2}, {0,2}, {0,1}, {-1}}, 
        {{3,2}, {3,3}, {4,3}, {4,2}, {-1}}, {{2,5}, {2,6}, {3,6}, {3,5}, {-1}}}, 
    {{	{1,1}, {6,6}, {5,7}, {0,2}, {-1}}, 					// %
        {{4,1}, {6,1}, {6,3}, {4,3}, {-1}}, {{0,5}, {2,5}, {2,7}, {0,7}, {-1}}},
    {{	{2,1}, {4,1}, {4,3}, {6,3}, {6,5}, {4,5}, {4,7}, {2,7}, {2,5}, {0,5},	// &
        {0,3}, {2,3}, {-1}}, {{-1}}, {{-1}}},
    {{	{0,5}, {1,5}, {2,6}, {2,8}, {0,8}, {-1}}, {{-1}}, {{-1}}},		// '
    {{	{1,0}, {3,0}, {3,2}, {2,2}, {2,6}, {3,6}, {3,8}, {1,8}, {0,7}, {0,1},	// ka
        {-1}}, {{-1}}, {{-1}}},
    {{	{0,0}, {2,0}, {3,1}, {3,7}, {2,8}, {0,8}, {0,6}, {1,6}, {1,2}, {0,2},	// kz
        {-1}}, {{-1}}, {{-1}}}, 
    {{	{-1}}, {{-1}}, {{-1}}}, 						// *
    {{	{2,1}, {4,1}, {4,3}, {6,3}, {6,5}, {4,5}, {4,7}, {2,7}, {2,5}, {0,5},	// +
        {0,3}, {2,3}, {-1}}, {{-1}}, {{-1}}},
    {{	{0,0}, {1,0}, {2,1}, {2,3}, {0,3}, {-1}}, {{-1}}, {{-1}}},		// ,
    {{	{0,3}, {5,3}, {5,5}, {0,5}, {-1}}, {{-1}}, {{-1}}},			// -
    {{	{0,1}, {2,1}, {2,3}, {0,3}, {-1}}, {{-1}}, {{-1}}}, 			// .
    {{	{1,1}, {6,6}, {5,7}, {0,2}, {-1}}, {{-1}}, {{-1}}}, 			// /
    {{	{1,0}, {5,0}, {6,1}, {6,7}, {5,8}, {1,8}, {0,7}, {0,1}, {-1}},		// 0
     {	{2,2}, {4,4}, {4,2}, {-1}}, { {2,4}, {2,6}, {4,6}, {-1}}},
    {{	{2,0}, {4,0}, {4,8}, {2,8}, {0,6}, {0,4}, {1,4}, {2,5}, {-1}},		// 1
        {{-1}}, {{-1}}},
    {{	{0,0}, {6,0}, {6,2}, {3,2}, {6,5}, {6,7}, {5,8}, {1,8}, {0,7}, {0,5},	// 2
        {2,5}, {2,6}, {4,6}, {0,2}, {-1}}, {{-1}}, {{-1}}},
    {{	{1,0}, {5,0}, {6,1}, {6,7}, {5,8}, {1,8}, {0,7}, {0,6}, {4,6}, {4,5},   // 3 
        {2,5}, {2,3}, {4,3}, {4,2}, {0,2}, {0,1}, {-1}}, {{-1}}, {{-1}}},
    {{	{4,0}, {6,0}, {6,8}, {4,8}, {4,5}, {2,5}, {2,8}, {0,8}, {0,3}, {4,3},	// 4
        {-1}}, {{-1}}, {{-1}}}, 
    {{	{0,0}, {5,0}, {6,1}, {6,4}, {5,5}, {2,5}, {2,6}, {6,6}, {6,8}, {0,8},	// 5
        {0,3}, {4,3}, {4,2}, {0,2}, {-1}}, {{-1}}, {{-1}}},
    {{	{1,0}, {5,0}, {6,1}, {6,4}, {5,5}, {2,5}, {2,6}, {5,6}, {5,8}, {1,8},	// 6
        {0,7}, {0,1}, {-1}}, 
        {{2,2}, {2,3}, {4,3}, {4,2}, {-1}}, {{-1}}},
    {{	{0,0}, {1,0}, {6,5}, {6,8}, {0,8}, {0,6}, {4,6}, {0,2}, {-1}}, 		// 7
        {{-1}}, {{-1}}}, 	
    {{	{1,0}, {5,0}, {6,1}, {6,3}, {5,4}, {6,5}, {6,7}, {5,8}, {1,8}, {0,7},	// 8 
        {0,5}, {1,4}, {0,3}, {0,1}, {-1}},
        {{2,5}, {2,6}, {4,6}, {4,5}, {-1}}, {{2,2}, {2,3}, {4,3}, {4,2}, {-1}}},
    {{	{1,0}, {5,0}, {6,1}, {6,7}, {5,8}, {1,8}, {0,7}, {0,4}, {1,3}, {4,3},	// 9
        {4,2}, {1,2}, {-1}}, {{2,5}, {2,6}, {4,6}, {4,5}, {-1}}, {{-1}}},
    {{	{0,1}, {2,1}, {2,3}, {0,3}, {-1}}, 					// :
        {{0,5}, {2,5}, {2,7}, {0,7}, {-1}}, {{-1}}}, 
    {{	{0,0}, {1,0}, {2,1}, {2,3}, {0,3}, {-1}}, 				// ; 
        {{0,5}, {2,5}, {2,7}, {0,7},  {-1}}, {{-1}}},
    {{	{4,0}, {5,0}, {5,2}, {3,4}, {5,6}, {5,8}, {4,8}, {0,4}, {-1}},		// <
        {{-1}}, {{-1}}},
    {{	{0,1}, {5,1}, {5,3}, {0,3}, {-1}}, 					// =
        {{0,5}, {5,5}, {5,7}, {0,7}, {-1}}, {{-1}}},
    {{	{0,0}, {1,0}, {5,4}, {1,8}, {0,8}, {0,6}, {2,4}, {0,2}, {-1}},		// >
        {{-1}}, {{-1}}},
    {{	{2,3}, {4,3}, {6,5}, {6,7}, {5,8}, {1,8}, {0,7}, {0,6}, {4,6}, {2,4},	// ?
        {-1}}, {{2,0}, {4,0}, {4,2}, {2,2}, {-1}}, {{-1}}},
    {{	{1,0}, {5,0}, {5,1}, {2,1}, {1,2}, {1,6}, {2,7}, {4,7}, {5,6}, {5,4},	// @
        {4,4}, {4,6}, {3,6}, {2,5}, {2,3}, {3,2}, {5,2}, {6,3}, {6,7}, {5,8}, 
        {1,8}, {0,7}, {0,1}, {-1}}, {{-1}}, {{-1}}},
    {{	{0,0}, {2,0}, {2,3}, {4,3}, {4,0}, {6,0}, {6,7}, {5,8}, {1,8}, {0,7},	// a
        {-1}}, {{2,5}, {2,6}, {4,6}, {4,5}, {-1}}, {{-1}}},
    {{	{0,0}, {5,0}, {6,1}, {6,3}, {5,4}, {6,5}, {6,7}, {5,8}, {0,8}, {-1}},	// b
        {{2,5}, {2,6}, {4,6}, {4,5}, {-1}}, {{2,2}, {2,3}, {4,3}, {4,2}, {-1}}},
    {{	{1,0}, {5,0}, {5,2}, {2,2}, {2,6}, {5,6}, {5,8}, {1,8}, {0,7}, {0,1},	// c
        {-1}}, {{-1}}, {{-1}}},
    {{	{0,0}, {5,0}, {6,1}, {6,7}, {5,8}, {0,8}, {-1}}, 			// d
     {	{2,2}, {2,6}, {4,6}, {4,2}, {-1}}, {{-1}}},
    {{	{0,0}, {6,0}, {6,2}, {2,2}, {2,3}, {6,3}, {6,5}, {2,5}, {2,6}, {6,6},	// e
        {6,8}, {0,8}, {-1}}, {{-1}}, {{-1}}}, 
    {{	{0,0}, {2,0}, {2,3}, {6,3}, {6,5}, {2,5}, {2,6}, {6,6}, {6,8}, {0,8},	// f
        {-1}}, {{-1}}, {{-1}}},
    {{	{1,0}, {5,0}, {6,1}, {6,5}, {4,5}, {4,2}, {2,2}, {2,6}, {6,6}, {6,8},	// g
        {1,8}, {0,7}, {0,1}, {-1}}, {{-1}}, {{-1}}},
    {{	{0,0}, {2,0}, {2,3}, {4,3}, {4,0}, {6,0}, {6,8}, {4,8}, {4,5}, {2,5},	// h
        {2,8}, {0,8}, {-1}}, {{-1}}, {{-1}}},
    {	{{0,0}, {2,0}, {2,8}, {0,8}, {-1}}, {{-1}}, {{-1}}},			// i
    {{	{1,0}, {5,0}, {6,1}, {6,8}, {0,8}, {0,6}, {4,6}, {4,2}, {2,2}, {2,4},	// j
        {0,4}, {0,1}, {-1}}, {{-1}}, {{-1}}},
    {{	{0,0}, {2,0}, {2,3}, {5,0}, {6,0}, {6,2}, {4,4}, {6,6}, {6,8}, {5,8},   // k
        {2,5}, {2,8}, {0,8}, {-1}}, {{-1}}, {{-1}}},
    {	{{0,0}, {5,0}, {5,2}, {2,2}, {2,8}, {0,8}, {-1}},			// l
        {{-1}}, {{-1}}},
    {{	{0,0}, {2,0}, {2,5}, {3,4}, {4,5}, {4,0}, {6,0}, {6,8}, {4,8}, {3,7},	// m 
        {2,8}, {0,8}, {-1}}, {{-1}}, {{-1}}}, 
    {{	{0,0}, {2,0}, {2,5}, {4,3}, {4,0}, {6,0}, {6,8}, {4,8}, {4,6}, {2,8},	// n
        {0,8}, {-1}}, {{-1}}, {{-1}}}, 
    {{	{1,0}, {5,0}, {6,1}, {6,7}, {5,8}, {1,8}, {0,7}, {0,1}, {-1}},		// o
     {	{2,2}, {2,6}, {4,6}, {4,2}, {-1}}, {{-1}}},
    {{	{0,0}, {2,0}, {2,3}, {5,3}, {6,4}, {6,7}, {5,8}, {0,8}, {-1}},		// p
        {{2,5}, {2,6}, {4,6}, {4,5}, {-1}}, {{-1}}},
    {{	{1,0}, {5,0}, {6,1}, {6,7}, {5,8}, {1,8}, {0,7}, {0,1}, {-1}},		// q
     {	{2,2}, {3,2}, {2,3}, {3,4}, {4,3}, {4,6}, {2,6}, {-1}}, {{-1}}},
    {{	{0,0}, {2,0}, {2,3}, {3,3}, {4,2}, {4,0}, {6,0}, {6,3}, {5,4}, {6,5},   // r
        {6,7}, {5,8}, {0,8}, {-1}}, 
     {	{2,5}, {2,6}, {4,6}, {4,5}, {-1}}, {{-1}}}, 
    {{	{0,0}, {5,0}, {6,1}, {6,4}, {5,5}, {2,5}, {2,6}, {6,6}, {6,8}, {1,8},	// s
        {0,7}, {0,4}, {1,3}, {4,3}, {4,2}, {0,2}, {-1}}, {{-1}}, {{-1}}}, 
    {{	{2,0}, {4,0}, {4,6}, {6,6}, {6,8}, {0,8}, {0,6}, {2,6}, {-1}},		// t
     {	{-1}}, {{-1}}}, 
    {{	{1,0}, {5,0}, {6,1}, {6,8}, {4,8}, {4,2}, {2,2}, {2,8}, {0,8}, {0,1}, 	// u
        {-1}}, {{-1}}, {{-1}}}, 
    {{	{3,0}, {6,3}, {6,8}, {4,8}, {4,4}, {3,3}, {2,4}, {2,8}, {0,8}, {0,3},	// v
        {-1}}, {{-1}}, {{-1}}}, 
    {{	{0,0}, {2,0}, {3,1}, {4,0}, {6,0}, {6,8}, {4,8}, {4,3}, {3,4}, {2,3},	// w
        {2,8}, {0,8}, {-1}}, {{-1}}, {{-1}}}, 
    {{	{0,0}, {2,0}, {2,2}, {3,3}, {4,2}, {4,0}, {6,0}, {6,3}, {5,4}, {6,5}, 	// x
        {6,8}, {4,8}, {4,6}, {3,5}, {2,6}, {2,8}, {0,8}, {0,5}, {1,4}, {0,3},
        {-1}}, {{-1}}, {{-1}}}, 
    {{	{2,0}, {4,0}, {4,3}, {6,5}, {6,8}, {4,8}, {4,6}, {3,5}, {2,6}, {2,8}, 	// y
        {0,8}, {0,5}, {2,3}, {-1}}, {{-1}}, {{-1}}}, 
    {{	{0,0}, {6,0}, {6,2}, {2.5,2}, {6,5.5}, {6,8}, {0,8}, {0,6}, {3.5,6},	// z
        {0,2.5}, {-1}}, {{-1}}, {{-1}}},
    {{	{0,9}, {2,9}, {2,10}, {0,10}, {-1}},					// dots for ü,ö and ä
        {{4,9}, {6,9}, {6,10}, {4,10}, {-1}}, {{-1}}},
    {{	{1,9}, {3,9}, {5,11}, {3,11}, {-1}},					// slash for ó,í, ú and é
        {{-1}}, {{-1}}},
    {{	{3,9}, {5,9}, {3,11}, {1,11}, {-1}},					// backslash for à
        {{-1}}, {{-1}}},        
    {{	{1,9}, {2,9}, {3,10}, {4,9}, {5,9}, {3,11}, {-1}},			// hat for ô
        {{-1}}, {{-1}}},
    {{	{1,9}, {2,9}, {3,10}, {4,9}, {6,11}, {5,11}, {4,10}, {3,11}, {-1}},	// tilde for ã
        {{-1}}, {{-1}}},
    {{	{2,0}, {3,-1}, {2,-2}, {3,-2}, {4,-1}, {3,-0}, {-1}},			// tail for ç
        {{-1}}, {{-1}}},
    {{	{1,9}, {5,9}, {5,12}, {1,12}, {-1}},					// circle for å
        {{2,10}, {2,11}, {4, 11}, {4,10}, {-1}}, {{-1}}},    
};

// __________________________________________________________________________________________________
KikiCharacter::KikiCharacter ( char c )
{
    addon = 0;

    if (c >= 97)
    {
        character = c - 65; // map lower case to upper case
    }
    else if (c < 0)
    {
		//KConsole::printf ("KikiCharacter::KikiCharacter character %c (%d)", c, c);
        switch (c)
        {
			case -68:  character = 52; addon = 1; break; // ¸
		    case -74:  character = 46; addon = 1; break; // ˆ
			case -76:  character = 46; addon = 4; break; // Ù
		    case -77:  character = 46; addon = 2; break; // Û
		    case -79:  character = 45; addon = 5; break; // Ò
			case -83:  character = 40; addon = 2; break; // Ì
			case -87:  character = 36; addon = 2; break; // È
			case -89:  character = 34; addon = 6; break; // Á
			case -91:  character = 32; addon = 7; break; // Â
		    case -92:  character = 32; addon = 1; break; // ‰
			case -93:  character = 32; addon = 5; break; // „
			case -95:  character = 32; addon = 2; break; // ·
			case -96:  character = 32; addon = 3; break; // ‡

            default:
                KConsole::printf ("KikiCharacter::KikiCharacter unknown character %c (%d)", c, c);
                break;
        }
    }
    else
    {
        character = c - 33; // start at ascii '!'
    }
}

// __________________________________________________________________________________________________
float KikiCharacter::getWidth () const
{
    float maxWidth = 0.0;
    int index = 0;
    while (KikiCharacterData[character][0][index].x >= 0)
    {
        float x = KikiCharacterData[character][0][index].x;
        if (x > maxWidth) maxWidth = x;
        index++;
    }
    
    return maxWidth;
}

// __________________________________________________________________________________________________
void KikiCharacter::display ()
{
    glPushMatrix();
    position.glTranslate();
    render();
    if (addon) renderCharacter (57+addon);
    glPopMatrix();
}

// __________________________________________________________________________________________________
void KikiCharacter::renderAddon ()
{
    if (addon == 4) // umlaute dots
    {
        glTranslatef (0,8,0);
        renderCharacter (13);
        glTranslatef (4,0,0);
        renderCharacter (13);
    }
}

// __________________________________________________________________________________________________
void KikiCharacter::render ()
{
    int list_color = KikiText::list_color;
        
    if (list_color >= 0 && KikiText::display_lists[list_color][character])
    {
        glCallList (KikiText::display_lists[list_color][character]);
    }
    else
    {
        if (list_color >= 0)
        {
            KikiText::display_lists[list_color][character] = glGenLists(1);
            if (KikiText::display_lists[list_color][character])
            {
                glNewList (KikiText::display_lists[list_color][character], GL_COMPILE_AND_EXECUTE);
            }
        }

        renderCharacter (character);
        
        if (list_color >= 0 && KikiText::display_lists[list_color][character])
        {
            glEndList();
        }
    }
}

// __________________________________________________________________________________________________
void KikiCharacter::renderCharacter ( char c )
{
	int contourIndex;
    GLUtesselator * tess = gluNewTess ();
    
    gluTessNormal (tess, 0.0, 0.0, 1.0);
    glNormal3f (0.0, 0.0, 1.0);

#ifndef WIN32
    gluTessCallback (tess, GLU_TESS_BEGIN, (GLvoid (*)())glBegin);
    gluTessCallback (tess, GLU_TESS_VERTEX, (GLvoid (*)())glVertex3dv);
    gluTessCallback (tess, GLU_TESS_END, (GLvoid (*)())glEnd);
#else
	  gluTessCallback (tess, GLU_TESS_BEGIN, (void (__stdcall *)())glBegin);
    gluTessCallback (tess, GLU_TESS_VERTEX, (void (__stdcall *)())glVertex3dv);
    gluTessCallback (tess, GLU_TESS_END, (void (__stdcall *)())glEnd);
#endif

    gluTessBeginPolygon (tess, NULL);
    for (contourIndex = 0; contourIndex < 3; contourIndex++)
    {
        int index = 0;
        gluTessBeginContour (tess);
        while (KikiCharacterData[c][contourIndex][index].x >= 0)
        {
            gluTessVertex(tess, (GLdouble*)&KikiCharacterData[c][contourIndex][index], 
                                &KikiCharacterData[c][contourIndex][index]);
            index++;
        }
        gluTessEndContour (tess);
    }
    gluTessEndPolygon(tess);
    gluDeleteTess(tess);
    
    float color_values[4];
    glGetFloatv (GL_CURRENT_COLOR, color_values);
    
    for (contourIndex = 0; contourIndex < 3; contourIndex++)
    {
        int index = 0;
        glBegin(GL_QUADS);
        while (KikiCharacterData[c][contourIndex][index].x >= 0)
        {
            GLdouble x = KikiCharacterData[c][contourIndex][index].x;
            GLdouble y = KikiCharacterData[c][contourIndex][index].y;

            GLdouble nx, ny;

            if (KikiCharacterData[c][contourIndex][index+1].x >= 0)
            {
                nx = KikiCharacterData[c][contourIndex][index+1].x;
                ny = KikiCharacterData[c][contourIndex][index+1].y;
            }
            else
            {                
                nx = KikiCharacterData[c][contourIndex][0].x;
                ny = KikiCharacterData[c][contourIndex][0].y;
            }
        
            KVector normal(KVector(0,0,-1).cross(KVector(nx,ny,0)-KVector(x,y,0)));
        
            glNormal3f(normal[X], normal[Y], normal[Z]);
            
            glVertex3f (x, y,  0.0);
            glColor4f  (color_values[R], color_values[G], color_values[B], 0.0);
            glVertex3f (x,   y, -KikiText::bevel_depth);
            glVertex3f (nx, ny, -KikiText::bevel_depth);
            glColor4fv (color_values);
            glVertex3f (nx, ny,  0.0);
            
            index++;
        }
        
        glEnd();
    }
}
