#ifndef __DUNE_NUMPROC_HH__
#define __DUNE_NUMPROC_HH__


namespace Dune {

    class NumProc
    {
    public:

        enum VerbosityMode {QUIET, REDUCED, FULL};

        VerbosityMode verbosity_;

    };

} // namespace Dune

#endif
