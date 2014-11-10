/* 
 * File:   FairMQTemplate.h
 * Author: winckler
 *
 * Created on November 19, 2014, 4:50 PM
 */

#ifndef FAIRMQTEMPLATE_H
#define	FAIRMQTEMPLATE_H


#include <iostream>
#include <type_traits>
#include <tuple>
#include <string>




namespace FairMQTemplate
{
    
    /// ///////////////////////// to print tuple elements ////////////////////////////////////////////
    /// Define a type which holds an unsigned integer value
    template<std::size_t> 
        struct int_{};

    template <class Tuple, size_t Pos>
        std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos> ) 
        {
            out << std::get< std::tuple_size<Tuple>::value-Pos >(t) << ',';
            return print_tuple(out, t, int_<Pos-1>());
        }

    template <class Tuple>
        std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1> ) 
        {
            return out << std::get<std::tuple_size<Tuple>::value-1>(t);
        }

    template <class... Args>
        std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t) 
        {
            out << '(';
            print_tuple(out, t, int_<sizeof...(Args)>());
            return out << ')';
        }

    
    
    namespace ResolvedTool
    {
        
        
        /// ////////////////////////////////////////////////////////////////////////
        /// test function member signature in given class
        namespace details 
        {
            ///////////////////////////////////////////////////////////////////////////
            // test whether T has SetFileProperties member function
            template<class T, class Sig, class=void>
                struct has_SetFileProperties:std::false_type{};

            template<class T, class R, class... Args>
                struct has_SetFileProperties<T, R(Args...),
                    typename std::enable_if<
                      std::is_convertible<
                        decltype(std::declval<T>().SetFileProperties(std::declval<Args>()...)),
                        R
                      >::value
                      || std::is_same<R, void>::value // all return types are compatible with void
                      // and, due to SFINAE, we can invoke T.foo(Args...) (otherwise previous clause fails)
                    >::type
                  >:std::true_type{};

            ///////////////////////////////////////////////////////////////////////////
            // test whether T has InitTClonesArray member function
            template<class T, class Sig, class=void>
                struct has_InitTClonesArray:std::false_type{};

            template<class T, class R, class... Args>
                struct has_InitTClonesArray<T, R(Args...),
                    typename std::enable_if<
                      std::is_convertible<
                        decltype(std::declval<T>().InitTClonesArray(std::declval<Args>()...)),
                        R
                      >::value
                      || std::is_same<R, void>::value // all return types are compatible with void
                      // and, due to SFINAE, we can invoke T.foo(Args...) (otherwise previous clause fails)
                    >::type
                  >:std::true_type{};

        }

        template<class T, class Sig>
            using has_SetFileProperties = std::integral_constant<bool, details::has_SetFileProperties<T, Sig>::value>;

        template<class T, class Sig>
            using has_InitTClonesArray = std::integral_constant<bool, details::has_InitTClonesArray<T, Sig>::value>;
    
    
        //-------------------------- for dependency injection pattern---------------------------------------------
        /*
        class Resolver 
        {
            public:
            static std::map<std::string, void *> registeredTypes;
            template<class T> 
                static void Register(const T* object)
                {
                    registeredTypes[typeid(T).name()] = (void *)object;
                }
            
            template<class T> 
                static T* Resolve()
                {
                    return (T *)registeredTypes[typeid(T).name()];
                }
        };
        class Resolver {
            public:
              static std::map<std::string, void *> registeredTypes;
              template<class T> static void Register(const T*);
              template<class T> static T* Resolve();
          };

          std::map<std::string, void *> Resolver::registeredTypes;

          template<class T> void Resolver::Register(const T* object) {
              registeredTypes[typeid(T).name()] = (void *)object;
          }

          template<class T> T* Resolver::Resolve() {
              return (T *)registeredTypes[typeid(T).name()];
          }*/

        
    }
    
    

    namespace MQDeviceTool
    {
        // handle different GenericFileSink policy API 
        //template <typename... Ts>
            class SinkHelper
            {

                    //templated typedef for better readability
                    template <typename T> 
                        using OneArgPolicy=ResolvedTool::has_SetFileProperties<T,void(const std::string&)> ;
                    
                    template <typename T>
                        using RootOutPolicy=ResolvedTool::has_SetFileProperties<T,void(const std::string&, const std::string&, const std::string&,const std::string&, const std::string&, bool,bool)> ;
                    
                    template <typename T>
                        using TClonesArrPolicy=ResolvedTool::has_InitTClonesArray<T,void(const std::string&)> ;

                    template< bool cond, typename U >
                        using resolvedType  = typename std::enable_if< cond, U >::type; 

                public: 
                        
                     SinkHelper(const std::string& filename, const std::string& classname="",
                                const std::string& treename="", const std::string& branchname="", 
                                const std::string& Fileoption="RECREATE", 
                                bool usecloneArr=false, bool flowmode=true
                                ) : 
                        fFilename(filename),
                        fClassname(classname),
                        fTreename(treename),
                        fBranchname(branchname),
                        fFileoption(Fileoption),
                        fUseTClonesArr(usecloneArr),
                        fFlowMode(flowmode){}
                    
                    ~SinkHelper(){}
                    

                    // enable if Binary storage policy
                    template <typename  T, resolvedType<OneArgPolicy<T>::value,int> = 0>
                        void SetProperties(T &obj)
                        {
                            if(!fFilename.empty())
                            {
                                obj.SetFileProperties(fFilename);
                                if(!fClassname.empty()) 
                                    InitTClonesArray(obj, fClassname);
                                obj.InitOutputFile();
                            }
                        }

                    // enable if Root storage policy
                    template <typename  T, resolvedType<RootOutPolicy<T>::value,int> = 0>
                        void SetProperties(T &obj)
                        {
                            if(!fFilename.empty())
                            {
                                obj.SetFileProperties(fFilename,fTreename,fBranchname,fClassname,
                                                      fFileoption,fUseTClonesArr,fFlowMode);
                                if(!fClassname.empty()) 
                                    InitTClonesArray(obj, fClassname);
                                obj.InitOutputFile();
                            }
                        }
                    
                    // enable if neither Root nor binary storage policy
                    template <typename  T, resolvedType<
                                !RootOutPolicy<T>::value && !OneArgPolicy<T>::value
                                ,int> = 0>
                        void SetProperties(T &obj)
                        {
                            std::cout<<"Sinkhelper does not support this API"<<std::endl;
                        }

                protected:

                    // version when T=InputPolicy has a void InputPolicy::InitTClonesArray(const string&) member function
                    template <typename  T, resolvedType< TClonesArrPolicy<T>::value,int> = 0>
                        void InitTClonesArray(T &obj, const std::string& classname)
                        {
                            obj.InitTClonesArray(classname);
                        }

                    // version when T=InputPolicy has no void InputPolicy::InitTClonesArray(const string&) member function
                    template <typename  T, resolvedType< !TClonesArrPolicy<T>::value,int> = 0>
                        void InitTClonesArray(T &obj, const std::string& classname)
                        {
                            //std::cout<<"No void T::InitTClonesArray(const string& classname) member found in given object."<<std::endl;
                        }

                private:

                    
                    std::string fFilename;
                    std::string fClassname;
                    std::string fTreename;
                    std::string fBranchname;
                    std::string fFileoption;
                    bool fUseTClonesArr;
                    bool fFlowMode;
            };

        
        
    }

    
}


#endif	/* FAIRMQTEMPLATE_H */

