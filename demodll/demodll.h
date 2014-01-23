//demodll.h

namespace demodll
{
	class myDemoFunc
	{
	public:
		static __declspec(dllexport) int demofunc(int a);
	};
}