#ifndef _MAGNETIZATION_H
#define _MAGNETIZATION_H

#include "VectorQuantity.h"

/*! \brief Class to measure the uniform magnetization along x, y and z.
 * Magnetization transverse is only measurable if the wavefunction
 * is not written such that Sztot is conserved
 */

class Magnetization: public VectorQuantity {
    public:
        Magnetization(const Stepper* stepper, FileManager* fm);
        virtual ~Magnetization();
        virtual void measure();
};

#endif