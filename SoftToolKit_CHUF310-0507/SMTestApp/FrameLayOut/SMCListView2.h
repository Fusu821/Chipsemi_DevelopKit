#pragma once

namespace SOUI{
	class SHeaderCtrl2 : public SHeaderCtrl
	{
		SOUI_CLASS_NAME(SHeaderCtrl2,L"header2")
	public:
		SHeaderCtrl2()
		{

		}
		virtual ~SHeaderCtrl2()
		{

		}

		void OnSize( UINT32 nType, CSize size )
		{
			int itemCount = GetItemCount();
			int totalWidth = GetTotalWidth();

			for( int index = 0; index < itemCount; index++ )
			{
				m_arrItems[index].cx.setSize( (float)GetItemWidth( index ) * size.cx / totalWidth, SLayoutSize::px );
			}

			return SHeaderCtrl::OnSize( nType, size );
		}
	protected:
		SOUI_MSG_MAP_BEGIN()
			MSG_WM_SIZE(OnSize)
		SOUI_MSG_MAP_END()
	};
}