/* CALCPrefsBox.cpp
 * Copyright (C) 2002 Dustin Graves <dgraves@computer.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "fox/fx.h"
#include "fox/FXElement.h"
#include "fox/FXArray.h"
#include "CALCdefs.h"
#include "CALCHelp.h"
#include "CALCWindow.h"
#include "CALCPrefsBox.h"

FXIMPLEMENT(CALCPrefsBox,FXDialogBox,NULL,0)

CALCPrefsBox::CALCPrefsBox(CALCWindow* owner)
: FXDialogBox(owner,"Preferences Box",DECOR_TITLE|DECOR_BORDER|DECOR_CLOSE|DECOR_MENU|DECOR_RESIZE,0,0,350,0, 0,0,0,0)
{
  FXVerticalFrame* contents=new FXVerticalFrame(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXHorizontalFrame* buttons=new FXHorizontalFrame(contents,LAYOUT_BOTTOM|LAYOUT_FILL_X);
  new FXButton(buttons,"&Close",NULL,this,FXDialogBox::ID_ACCEPT,BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
  new FXHorizontalSeparator(contents,SEPARATOR_RIDGE|LAYOUT_BOTTOM|LAYOUT_FILL_X);

  tabbook=new FXTabBook(contents,NULL,0,LAYOUT_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXTabItem* tab1=new FXTabItem(tabbook,"&Settings",NULL);
  FXVerticalFrame* settingsframe=new FXVerticalFrame(tabbook,FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  new FXLabel(settingsframe,"fxcalc settings");
  new FXHorizontalSeparator(settingsframe,SEPARATOR_LINE|LAYOUT_FILL_X);

  FXMatrix *matrix1=new FXMatrix(settingsframe,3,MATRIX_BY_ROWS|PACK_UNIFORM_HEIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  new FXLabel(matrix1,"Display Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix1,"Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix1,"Precision:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXButton(matrix1,"Set...",NULL,owner,CALCWindow::ID_DISPLAYFONT,FRAME_RAISED|FRAME_THICK|LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
  new FXButton(matrix1,"Set...",NULL,owner,CALCWindow::ID_BUTTONFONT,FRAME_RAISED|FRAME_THICK|LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
  FXSpinner* spinner=new FXSpinner(matrix1,5,owner,CALCWindow::ID_NUMDIGITS,JUSTIFY_RIGHT|FRAME_SUNKEN|FRAME_THICK|LAYOUT_CENTER_Y|LAYOUT_LEFT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW);
  spinner->setTipText(DIGITNUMDIGITS_HELP);
  spinner->setRange(0,CALCDBL_DIG+2);  //Give it a little extra


  FXTabItem* tab2=new FXTabItem(tabbook,"C&olors",NULL);
  FXVerticalFrame* colorframe=new FXVerticalFrame(tabbook,FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  new FXLabel(colorframe,"fxcalc colors");
  new FXHorizontalSeparator(colorframe,SEPARATOR_LINE|LAYOUT_FILL_X);

  FXMatrix *matrix2=new FXMatrix(colorframe,5,MATRIX_BY_ROWS|PACK_UNIFORM_HEIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  new FXLabel(matrix2,"Display:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix2,"Digits:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix2,"Hex Digits:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix2,"Operators:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix2,"Functions:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_DISPLAY,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_DIGITS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_HEXDIGITS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_OPERATORS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_FUNCTIONS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);

  new FXLabel(matrix2,"Memory:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix2,"Statistics:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix2,"Backspace:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix2,"Clear Entry:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix2,"Clear All:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_MEMORY,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_STATISTICS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_BACKSPACE,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_CLEARENTRY,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix2,FXRGB(0,0,0),owner,CALCWindow::ID_COLOR_CLEARALL,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);

  FXTabItem* tab3=new FXTabItem(tabbook,"&Text Colors",NULL);
  FXVerticalFrame* textcolorframe=new FXVerticalFrame(tabbook,FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  new FXLabel(textcolorframe,"fxcalc text colors");
  new FXHorizontalSeparator(textcolorframe,SEPARATOR_LINE|LAYOUT_FILL_X);

  FXMatrix *matrix3=new FXMatrix(textcolorframe,5,MATRIX_BY_ROWS|PACK_UNIFORM_HEIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  new FXLabel(matrix3,"Display Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix3,"Digits Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix3,"Hex Digits Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix3,"Operators Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix3,"Functions Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_DISPLAY,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_DIGITS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_HEXDIGITS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_OPERATORS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_FUNCTIONS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);

  new FXLabel(matrix3,"Memory Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix3,"Statistics Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix3,"Backspace Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix3,"Clear Entry Font:",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXLabel(matrix3,"Clear All: Font",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X|LAYOUT_FILL_ROW);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_MEMORY,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_STATISTICS,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_BACKSPACE,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_CLEARENTRY,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
  new FXColorWell(matrix3,FXRGB(0,0,0),owner,CALCWindow::ID_TEXTCOLOR_CLEARALL,COLORWELL_OPAQUEONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_RIGHT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT|LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW,0,0,40,24);
}

CALCPrefsBox::~CALCPrefsBox()
{
}

void CALCPrefsBox::setPrefTab(FXuint tab)
{
  tabbook->handle(this,MKUINT(FXTabBar::ID_OPEN_FIRST+tab,SEL_COMMAND),NULL);
}