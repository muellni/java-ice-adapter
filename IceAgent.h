#pragma once

#include <string>
#include <memory>
#include <map>

#include "IceAdapterOptions.h"
#include "IceStream.h"

typedef struct _NiceAgent NiceAgent;
typedef struct _GMainLoop GMainLoop;
typedef struct _NiceCandidate NiceCandidate;

namespace faf
{

class IceAdapterOptions;

class IceAgent : public std::enable_shared_from_this<IceAgent>
{
public:
  IceAgent(GMainLoop* mainloop,
           IceAdapterOptions const& options);
  virtual ~IceAgent();

  NiceAgent* handle() const;

  IceStreamPtr createStream(int peerId,
                            IceStream::SdpCallback sdpCallback,
                            IceStream::ReceiveCallback receiveCallback,
                            IceStream::StateCallback stateCallback,
                            IceStream::CandidateSelectedCallback candidateSelectedCallback,
                            IceStream::ConnectivityChangedCallback connectivityChangedCallback);

  void removeStream(int peerId);
  void clear();

  GMainLoop* mainloop() const;
protected:

  NiceAgent* mHandle;
  GMainLoop* mMainloop;
  IceAdapterOptions mOptions;
  std::map<int, IceStreamPtr> mPeerStreams;
  std::map<unsigned int, IceStreamPtr> mSteamIdStreams;

  friend void cb_candidate_gathering_done(NiceAgent*,
                                          unsigned int,
                                          void*);
  friend void cb_component_state_changed(NiceAgent *agent,
                                         unsigned int,
                                         unsigned int,
                                         unsigned int,
                                         void*);
  friend void cb_new_selected_pair_full(NiceAgent*,
                                        unsigned int,
                                        unsigned int,
                                        NiceCandidate*,
                                        NiceCandidate*,
                                        void*);
  friend void cb_new_candidate(NiceAgent*,
                               NiceCandidate*,
                               void*);
  friend void cb_stream_writeable(NiceAgent*,
                                  unsigned int,
                                  unsigned int,
                                  void*);
};
typedef std::shared_ptr<IceAgent> IceAgentPtr;

}
