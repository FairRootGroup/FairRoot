

//#include "FairSource.h"

#include "BaseSourcePolicy.h"
#include "FairMQLogger.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"

#include "FairFileSource.h"
#include "FairLmdSource.h"
#include "FairMbsSource.h"
#include "FairMbsStreamSource.h"
#include "FairMixedSource.h"
#include "FairRemoteSource.h"



#include <type_traits>
#include <functional>


template<typename T, typename U>
using enable_if_match = typename std::enable_if<std::is_same<T,U>::value,int>::type;


template<typename FairSourceType, typename DataType>
class FairSourceMQInterface : public BaseSourcePolicy< FairSourceMQInterface<FairSourceType, DataType> >
{
	typedef DataType* DataType_ptr;
	typedef FairSourceMQInterface<FairSourceType,DataType> this_type;
public:
	FairSourceMQInterface() : 
			BaseSourcePolicy<FairSourceMQInterface<FairSourceType, DataType>>(), 
			fSource(nullptr), 
			fData(nullptr), 
			fIndex(0),
			fMaxIndex(-1),
			fSourceName(),
			fBranchName(),
			fRunAna(nullptr),
			fRunOnline(nullptr),
			fCustomRO(false),
			fCustomRA(false),
			fCustomInitSourceRO(),
			fCustomInitSourceRA()

	{
	}

	virtual ~FairSourceMQInterface() 
	{
		if(fData)
			delete fData;
		fData=nullptr;
		if(fSource)
			delete fSource;
		fSource=nullptr;
		if(fRunAna)
			delete fRunAna;
		fRunAna=nullptr;
		if(fRunOnline)
			delete fRunOnline;
		fRunOnline=nullptr;
	}

	//______________________________________________________________________________
	// Custom source init via lambda

	template <typename Lambda>
	void CustomInitSourceRunOnline(Lambda func)
	{
		fCustomRO=true;
		fCustomInitSourceRO=func;
	}

	template <typename Lambda>
	void CustomInitSourceRunAna(Lambda func)
	{
		fCustomRA=true;
		fCustomInitSourceRA=func;
	}

	int64_t GetNumberOfEvent()
	{
		return fMaxIndex;
	}

	void SetFileProperties(const std::string &filename, const std::string &branchname)
    {
        fSourceName = filename;
        fBranchName = branchname;
    }


	//______________________________________________________________________________
	// FairFileSource

	template <typename T = FairSourceType, enable_if_match<T, FairFileSource> = 0>
	void InitSource()
	{
		if(fCustomRA)
		{
			fCustomInitSourceRA(&fSource,&fData,&fRunAna);
		}
		else
		{
			fRunAna = new FairRunAna();
			fSource = new FairSourceType(fSourceName.c_str());
			fSource->Init();
			fSource->ActivateObject((TObject**)&fData,fBranchName.c_str());
			
		}
		fMaxIndex = fSource->CheckMaxEventNo();
	}

	template <typename T = FairSourceType, enable_if_match<T, FairFileSource> = 0>
	void SetIndex(int64_t eventIdx)
	{
		fIndex=eventIdx;

	}

	template <typename T = FairSourceType, enable_if_match<T, FairFileSource> = 0>
 	DataType_ptr GetOutData()
 	{
		fSource->ReadEvent(fIndex);
		return fData;
 	}

	//______________________________________________________________________________
	// FairLmdSource

	template <typename T = FairSourceType, enable_if_match<T, FairLmdSource> = 0>
	void InitSource()
	{
		LOG(INFO)<<"start of out Lambda";
		fCustomInitSourceRO(&fSource,fData,&fRunOnline);
		LOG(INFO)<<"End of out Lambda";
	}

	template <typename T = FairSourceType, enable_if_match<T, FairLmdSource> = 0>
	void SetIndex(int64_t eventIdx)
	{
		//fSource->Reset();
		fIndex=eventIdx;
	}
	
	template <typename T = FairSourceType, enable_if_match<T, FairLmdSource> = 0>
	void Reset()
	{
		fSource->Reset();
	}
	
	template <typename T = FairSourceType, enable_if_match<T, FairLmdSource> = 0>
 	DataType_ptr GetOutData()
 	{
		fSource->ReadEvent();
		return fData;
 	}

	template <typename T = FairSourceType, enable_if_match<T, FairLmdSource> = 0>
 	void SetMaxIndex(int64_t max)
 	{
 		fMaxIndex=max;
 	}

 	/*
	//______________________________________________________________________________
	// FairMbsSource
	template <typename T = FairSourceType, enable_if_match<T, FairMbsSource> = 0>
	void InitSource()
	{
		fRunAna = new FairRunAna();
		fSource = new FairSourceType();
		fSource->Init();
		fSource->ActivateObject((TObject**)&fData,fBranchName.c_str());
	}


	//______________________________________________________________________________
	// FairMbsStreamSource
	template <typename T = FairSourceType, enable_if_match<T, FairMbsStreamSource> = 0>
	void InitSource()
	{
		fRunAna = new FairRunAna();
		fSource = new FairSourceType(fSourceName.c_str());
		fSource->Init();
		fSource->ActivateObject((TObject**)&fData,fBranchName.c_str());
	}

	//______________________________________________________________________________
	// FairMixedSource
	template <typename T = FairSourceType, enable_if_match<T, FairMixedSource> = 0>
	void InitSource()
	{
		fRunAna = new FairRunAna();
		fSource = new FairSourceType(fSourceName.c_str());
		fSource->Init();
		fSource->ActivateObject((TObject**)&fData,fBranchName.c_str());
	}

	//______________________________________________________________________________
	// FairRemoteSource
	template <typename T = FairSourceType, enable_if_match<T, FairRemoteSource> = 0>
	void InitSource()
	{
		fRunAna = new FairRunAna();
		fSource = new FairSourceType(fSourceName.c_str());
		fSource->Init();
		fSource->ActivateObject((TObject**)&fData,fBranchName.c_str());
	}
	// */

	
protected:

 	FairSourceType* fSource;
 	DataType_ptr fData;
 	int64_t fIndex;
 	int64_t fMaxIndex;
 	std::string fClassName;
 	std::string fBranchName;
 	std::string fSourceName;
 	FairRunAna* fRunAna;
 	FairRunOnline* fRunOnline;

	bool fCustomRO;
	bool fCustomRA;
 	std::function<void(FairSourceType**,DataType_ptr,FairRunOnline**)> fCustomInitSourceRO;// when FairRunOnline required
 	std::function<void(FairSourceType**,DataType_ptr*,FairRunAna**)> fCustomInitSourceRA;// when FairRunAna required
    
};