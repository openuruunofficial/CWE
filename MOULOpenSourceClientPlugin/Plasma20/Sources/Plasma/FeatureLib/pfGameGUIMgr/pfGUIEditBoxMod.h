/*==LICENSE==*

CyanWorlds.com Engine - MMOG client, server and tools
Copyright (C) 2011 Cyan Worlds, Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Additional permissions under GNU GPL version 3 section 7

If you modify this Program, or any covered work, by linking or
combining it with any of RAD Game Tools Bink SDK, Autodesk 3ds Max SDK,
NVIDIA PhysX SDK, Microsoft DirectX SDK, OpenSSL library, Independent
JPEG Group JPEG library, Microsoft Windows Media SDK, or Apple QuickTime SDK
(or a modified version of those libraries),
containing parts covered by the terms of the Bink SDK EULA, 3ds Max EULA,
PhysX SDK EULA, DirectX SDK EULA, OpenSSL and SSLeay licenses, IJG
JPEG Library README, Windows Media SDK EULA, or QuickTime SDK EULA, the
licensors of this Program grant you additional
permission to convey the resulting work. Corresponding Source for a
non-source form of such a combination shall include the source code for
the parts of OpenSSL and IJG JPEG Library used as well as that of the covered
work.

You can contact Cyan Worlds, Inc. by email legal@cyan.com
 or by snail mail at:
      Cyan Worlds, Inc.
      14617 N Newport Hwy
      Mead, WA   99021

*==LICENSE==*/
//////////////////////////////////////////////////////////////////////////////
//																			//
//	pfGUIEditBoxMod Header													//
//																			//
//////////////////////////////////////////////////////////////////////////////

#ifndef _pfGUIEditBoxMod_h
#define _pfGUIEditBoxMod_h

#include "hsStlUtils.h"
#include "pfGUIControlMod.h"
#include "../pnInputCore/plKeyDef.h"

#include "../plInputCore/plInputDevice.h"

class plMessage;
class hsGMaterial;
class plTextGenerator;


class pfGUIEditBoxMod : public pfGUIControlMod
{
	protected:

		wchar_t			*fBuffer;
		UInt32			fBufferSize, fCursorPos;
		Int32			fScrollPos;
		hsBool			fIgnoreNextKey, fEscapedFlag;
		hsBool			fFirstHalfExitKeyPushed;
		
		hsBool			fSpecialCaptureKeyEventMode;

		plKeyDef		fSavedKey;
		UInt8			fSavedModifiers;
		
		wchar_t			fLastDeadKey; // if the previous key was a dead key, its value goes here
		wchar_t			fDeadKeyConverter[256][256]; // first index is the dead key, second index is the char to combine it with

		virtual hsBool IEval( double secs, hsScalar del, UInt32 dirty ); // called only by owner object's Eval()

		virtual void	IPostSetUpDynTextMap( void );
		virtual void	IUpdate( void );

		void SetupDeadKeyConverter();

	public:
		enum
		{
			kShift	= 0x01,
			kCtrl	= 0x02
		};

		pfGUIEditBoxMod();
		virtual ~pfGUIEditBoxMod();

		CLASSNAME_REGISTER( pfGUIEditBoxMod );
		GETINTERFACE_ANY( pfGUIEditBoxMod, pfGUIControlMod );

		virtual hsBool	MsgReceive( plMessage* pMsg );
		
		virtual void Read( hsStream* s, hsResMgr* mgr );
		virtual void Write( hsStream* s, hsResMgr* mgr );

		virtual void	HandleMouseDown( hsPoint3 &mousePt, UInt8 modifiers );
		virtual void	HandleMouseUp( hsPoint3 &mousePt, UInt8 modifiers );
		virtual void	HandleMouseDrag( hsPoint3 &mousePt, UInt8 modifiers );

		virtual hsBool	HandleKeyPress( char key, UInt8 modifiers );
		virtual hsBool	HandleKeyEvent( pfGameGUIMgr::EventType event, plKeyDef key, UInt8 modifiers );

		virtual void	PurgeDynaTextMapImage();

		void	SetBufferSize( UInt32 size );

		std::string	GetBuffer( void );
		std::wstring	GetBufferW( void ) { return fBuffer; }
		void		ClearBuffer( void );
		void		SetText( const char *str );
		void		SetText( const wchar_t *str );

		void		SetCursorToHome( void );
		void		SetCursorToEnd( void );

		hsBool		WasEscaped( void ) { hsBool e = fEscapedFlag; fEscapedFlag = false; return e; }

		void		SetSpecialCaptureKeyMode(hsBool state) { fSpecialCaptureKeyEventMode = state; }
		UInt32		GetLastKeyCaptured() { return (UInt32)fSavedKey; }
		UInt8		GetLastModifiersCaptured() { return fSavedModifiers; }
		void		SetLastKeyCapture(UInt32 key, UInt8 modifiers);

		void		SetChatMode(hsBool state) { plKeyboardDevice::IgnoreCapsLock(state); }

		// Extended event types
		enum ExtendedEvents
		{
			kValueChanging
		};
};

#endif // _pfGUIEditBoxMod_h
