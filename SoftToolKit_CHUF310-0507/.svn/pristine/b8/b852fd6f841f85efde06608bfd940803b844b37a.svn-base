/***********************************************************************
Vczh Library++ 3.0
Developer: ³Âè÷å«(vczh)
Data Structure::Pair

Classes:
	Pair<K, V>							£º¶þÔª×é
***********************************************************************/

#ifndef VCZH_COLLECTIONS_PAIR
#define VCZH_COLLECTIONS_PAIR

#include "Basic.h"

namespace vl
{
	namespace collections
	{
		template<typename K, typename V>
		class Pair
		{
		public:
			K				key;
			V				value;

			Pair()
			{
			}

			Pair(const K& _key, const V& _value)
			{
				key=_key;
				value=_value;
			}

			Pair(const Pair<K, V>& pair)
			{
				key=pair.key;
				value=pair.value;
			}

			int CompareTo(const Pair<K, V>& pair)const
			{
				if(key<pair.key)
				{
					return -1;
				}
				else if(key>pair.key)
				{
					return 1;
				}
				else if(value<pair.value)
				{
					return -1;
				}
				else if(value>pair.value)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}

			bool operator==(const Pair<K, V>& pair)const
			{
				return CompareTo(pair)==0;
			}

			bool operator!=(const Pair<K, V>& pair)const
			{
				return CompareTo(pair)!=0;
			}

			bool operator<(const Pair<K, V>& pair)const
			{
				return CompareTo(pair)<0;
			}

			bool operator<=(const Pair<K, V>& pair)const
			{
				return CompareTo(pair)<=0;
			}

			bool operator>(const Pair<K, V>& pair)const
			{
				return CompareTo(pair)>0;
			}

			bool operator>=(const Pair<K, V>& pair)const
			{
				return CompareTo(pair)>=0;
			}
		};
	}

	template<typename K, typename V>
	struct POD<collections::Pair<K, V>>
	{
		static const bool Result=POD<K>::Result && POD<V>::Result;
	};
}

#endif