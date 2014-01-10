#ifndef _AMPLITUDE_H
#define _AMPLITUDE_H
#include "BigDouble.h"
#include "BigComplex.h"
#include "defs.h"

class WaveFunction_1;
class SpinState;

/*! \brief scalar product \f$\langle \{R_i,\sigma_i\}|\Psi\rangle\f$
 *
 * Class to calculate the scalar product between the real space spin state
 * \f$|{R_i,\sigma_i}\rangle\f$ (represented by the class SpinState) and the
 * trial wave function \f$|\Psi\rangle\f$ (represented by classes inheriting
 * from the class WaveFunction). The class uses the determinant and inverse
 * matrix update technique.
 * For a column vector \f$u\f$ update (hop in the trial wavefunction space):
 * \f[\frac{det(A')}{det(A)}=\frac{det(A+(u-Ae_k)e_k^T)}{det(A)}
 * =e_k^TA^{-1}u\f]
 * and
 * \f[(A')^{-1}=(A+(u-Ae_k)e_k^T)^{-1}=A^{-1}-\frac{(A^{-1}u-e_k)e_k^TA^{-1}}
 * {e_k^TA^{-1}u}\f]
 * For a row vector \f$v^T\f$ update (hop in the real space):
 * \f[\frac{det(A')}{det(A)}=\frac{det(A+e_r(v^T-e_r^TA))}{det(A)}
 * =v^TA^{-1}e_r\f]
 * and
 * \f[(A')^{-1}=(A+e_r(v^T-e_r^TA))^{-1}=
 * A^{-1}-\frac{A^{-1}e_r(v^TA^{-1}-e_r^T)}
 * {v^TA^{-1}e_r}.\f]
 * For a successive \f$r\f$ row and \f$k\f$ column update by repsectively
 * \f$v^T\f$ and \f$u\f$ vectors:
 * \f[\frac{det(A)}{det(A')}=\left|\begin{array}{cc}
 * e_k^TA^{-1}u+A^{-1}_{kr}A_{rk} & A^{-1}_{kr}\\
 * v^TA^{-1}u+A_{rk}v^TA^{-1}e_r-u_r+v_k(e_k^TA^{-1}u+A_{rk}A^{-1}_{kr}) &
 * v^TA^{-1}e_r-v_kA^{-1}_{kr}\end{array}\right|,\f]
 * and for a successive \f$k\f$ column and \f$r\f$ row update by repsectively
 * \f$u\f$ and \f$v^T\f$ vectors:
 * \f[\frac{det(A)}{det(A')}=\left|\begin{array}{cc}
 * e_k^TA^{-1}u-u_rA^{-1}_{kr} & A^{-1}_{kr}\\
 * v^TA^{-1}u-v_k+A_{rk}e_k^TA^{-1}u-u_r(v^TA^{-1}e_r+A_{rk}A^{-1}_{kr})
 * & v^TA^{-1}e_r+A_{rk}A^{-1}_{kr}\end{array}\right|.\f]
 */

class Amplitude_1 {
    public:
        Amplitude_1(SpinState* sp, WaveFunction_1* wav);//!< Constructor
        ~Amplitude_1();//!< Destructor
        /*! Initialize or reinitialize the matrices
         * Calculate determinant and inverse matrices.*/
        void Init();
        //! update matrices after a spin swap.
        void ColUpdate(const size_t& idup,
                       const size_t& iddo);
        /*! calculate the new determinant without updating
         * the inverse matrices*/
        BigComplex VirtColUpdate(const size_t& idup,
                                 const size_t& fup,
                                 const size_t& iddo,
                                 const size_t& fdo) const;
        //! update matrices after a hop in reciprocal space.
        void RowUpdate(const size_t& idup,
                       const size_t& iddo);
        /*! calculate the new determinant without updating
         * the inverse matrices*/
        BigComplex VirtRowUpdate(const size_t& idup,
                                 const size_t& rup,
                                 const size_t& iddo,
                                 const size_t& rdo) const;
        /*! gives the new determinants after the row update
         * specified by r(...) for all subsequent column updates
         * specified by k(...)*/
        void VirtUpdate(const std::vector<hop_path_t> rhopup,
                        const std::vector<hop_path_t> rhopdo,
                        const std::vector<hop_path_t> khopup,
                        const std::vector<hop_path_t> khopdo,
                        BigComplex* qs) const;

        void Update(const hop_path_t rhopup,
                    const hop_path_t rhopdo,
                    const hop_path_t khopup,
                    const hop_path_t khopdo);

        //! returns \f$\langle \{R_i,\sigma\}|\Psi\rangle\f$.
        BigComplex Amp() const;
        const SpinState* GetSpinState() const {return m_sp;}
        SpinState* GetSpinState() {return m_sp;}
        const WaveFunction_1* GetWaveFunction() const {return m_wav;}
        WaveFunction_1* GetWaveFunction() {return m_wav;}
    private:
        SpinState* m_sp;
        WaveFunction_1* m_wav;
        std::complex<double>* m_matup;
        std::complex<double>* m_matiup;
        std::complex<double>* m_matdo;
        std::complex<double>* m_matido;
        BigComplex m_amp;
        bool m_amp_ok;
        size_t m_Nup; //!< size of the up (square) matrices.
        size_t m_Ndo; //!< size of the down (square) matrices.


};

#endif//_AMPLITUDE_H