/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

#include <iostream>
#include <string>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deep_history.hpp>
#include <boost/statechart/shallow_history.hpp>


/**
 * Helpers
 * Makes it quick and easy to create entry and exit actions
 * -> constructor and destructor and have them write something to cout.
 *
 * Usage
 * struct Test
 * {
 *    PRINT_ENTRY_EXIT(0, Test)
 * };
 *
 * Note the missing ;
 * param 1 - Is state inner level - denoted on printout with '*'
 * param 2 - Is the name of the class in question. No quotes!
 */
void print(unsigned int lvl, const std::string& name)
{
    for(unsigned int i = 0; i< lvl; ++i)
        std::cout << "*";
    std::cout << " " << name << std::endl;
}

#define PRINT_ENTRY_EXIT(lvl, name)             \
  name() { print(lvl, #name"()"); }             \
  ~name() { print(lvl, "~"#name"()"); }



namespace sc = boost::statechart;

/**
 * Events that can be handled
 */

struct EvAMTuner : sc::event<EvAMTuner>{};
struct EvFMTuner : sc::event<EvFMTuner>{};
struct EvOn : sc::event<EvOn>{};
struct EvOff : sc::event<EvOff>{};
// new events"!
struct EvTuner : sc::event<EvTuner> {};
struct EvCD : sc::event<EvCD> {};
struct EvCDInserted : sc::event<EvCDInserted> {};
struct EvEject : sc::event<EvEject> {};
struct EvCDState : sc::event<EvCDState>{
    EvCDState(bool valid) : isValid(valid){};
    bool GetState() const {
        return isValid;
    }
    private:
    bool isValid;
};

/**
 * Machine definition and the top level states
 * forward declarations
 */
struct Off;
struct On;
struct MeanMachine : sc::state_machine<MeanMachine, Off>{
    bool cdIn = false;
    //empty struct

};

struct CDLoading;
struct CDPlaying;
struct RadioPlaying;

/**
 * On
 */
struct On : sc::simple_state<On, MeanMachine, boost::mpl::list<sc::deep_history<RadioPlaying>>, sc::has_deep_history>{
    PRINT_ENTRY_EXIT(0, On);
    typedef sc::transition<EvOff, Off> reactions;
};

/**
 * Off
 */
struct Off : sc::simple_state<Off, MeanMachine>{
    PRINT_ENTRY_EXIT(0, Off);
    typedef sc::transition<EvOn, On> reactions;
};

/**
 * Radioplaying
 */
struct FMTuner;
struct AMTuner;

struct RadioPlaying : sc::simple_state<RadioPlaying, On, boost::mpl::list<sc::shallow_history<FMTuner>>, sc::has_shallow_history>{
    PRINT_ENTRY_EXIT(1, RadioPlaying);
    typedef boost::mpl::list<sc::transition<EvCDInserted, CDLoading>, sc::custom_reaction<EvCD>> reactions;
    sc::result react(const EvCD& kalleNavn){
        if(context<MeanMachine>().cdIn){
            return transit<CDPlaying>();
        }
        std::cout << "No cd insertet" << std::endl;
        return discard_event();
    }
};

/**
 * FMTuner
 */

struct FMTuner : sc::simple_state<FMTuner, RadioPlaying>{
    PRINT_ENTRY_EXIT(2, FMTuner);
    typedef sc::transition<EvAMTuner, AMTuner> reactions;
};


/**
 * AMTuner
 */

struct AMTuner : sc::simple_state<AMTuner, RadioPlaying>{
    PRINT_ENTRY_EXIT(2, AMTuner);
    typedef sc::transition<EvFMTuner, FMTuner> reactions;
};

/**
 * CDLoading
 */
struct CDLoading : sc::simple_state<CDLoading, On>
{
    /* Missing code */
    typedef sc::custom_reaction<EvCDState> reactions;

    PRINT_ENTRY_EXIT(1, CDLoading);

    /* Missing code */
    sc::result react(const  EvCDState& kalleNavn){
        if(kalleNavn.GetState())
            return transit<CDPlaying>();
        else
            return transit<RadioPlaying>();
    }
};


/**
 * CDPlaying
 */
struct CDPlaying : sc::simple_state<CDPlaying, On>
{
    typedef sc::transition<EvTuner, RadioPlaying> reactions;

    PRINT_ENTRY_EXIT(1, CDPlaying);
};



int main()
{
    /* Instantiate State machine and make it process some relevant events... */

    MeanMachine MyMeanMachine;
    MyMeanMachine.initiate();
    //MyMeanMachine.cdIn = false;

    //std::cout << "Sending EvOn" << std::endl;
    MyMeanMachine.process_event(EvOn());
    //std::cout << "Sending EvAMTuner" << std::endl;
    MyMeanMachine.process_event(EvAMTuner());
    //std::cout << "Sending EvCDInserted" << std::endl;
    MyMeanMachine.process_event(EvCDInserted());
    //std::cout << "Sending EvCDState(true)" << std::endl;
    MyMeanMachine.process_event(EvCDState(true));
    //std::cout << "Sending EvTuner" << std::endl;
    MyMeanMachine.process_event(EvTuner());
    //std::cout << "Sending EvCD" << std::endl;
    MyMeanMachine.process_event(EvCD());
    MyMeanMachine.cdIn = true;

    //std::cout << "Sending EvCD" << std::endl;
    MyMeanMachine.process_event(EvCD());
    MyMeanMachine.process_event(EvTuner());
    //std::cout << "Sending EvOff" << std::endl;
    MyMeanMachine.process_event(EvOff());
    //std::cout << "Sending EvOn" << std::endl;
    MyMeanMachine.process_event(EvOn());
    //std::cout << "Sending EvTuner" << std::endl;
    MyMeanMachine.process_event(EvTuner());

    return 0;
}