# Photon-Interactions-Monte-Carlo
Research on the interaction of Photons with a material medium, using Monte Carlo methods, developed at the University of Lisbon. The computational part is done in C++, and the data analysis is done in Python with Matplotlib. It is highly suggested that one read the research paper .PDF's if they wish to understand the context behind the code, as the following descriptions only give brief outlines. The .PDF and images are in Portuguese according to the university's language.

## Description

The probability of interaction of a photon with a material medium per unit length is usually called the linear attenuation coefficient, $\mu$, and its inverse $\lambda = 1/ \mu$ is the attenuation length. This quantity can be expressed in terms of the effective section of interaction through

$\lambda = \frac{A}{\rho N_A \sigma}

where $\sigma$ is the effective section of the process, $\rho$ the density of the material, $N_A$ the Avogadro number and $A$ the mass number of the element. In general, the attenuation length for photons presents macroscopic values (of the order of mm or cm) allowing each photon to be simulated independently (a particle at a time).

For a monochromatic, monodirectional beam of photons (pencil beam), we consider valid the law of exponential attenuation,

$$  I = I_0 e^{-\mu x} $$

in which a beam initially containing $I_0$ photons is reduced to a number $I$ after crossing a thickness $x$ of material, with linear attenuation coefficient equal to $\mu$. Thus, $I/I_0$ is the fraction of photons that survive without interacting after a length $x$. The path length of a photon to the first interaction then follows an exponential distribution and can be generated randomly using the transformation method.

For photon energies between keV and MeV, the relevant interactions with the material medium are: absorption by photoelectric effect, elastic Rayleigh scattering (coherent) and inelastic Compton scattering (incoherent).
Each of these interactions has linear attenuation coefficients that depend on the medium and the energy of the photon, which can be obtained from a table. How the processes are independent, the total linear attenuation coefficient is the sum of the attenuation coefficients of the various possible processes,

$$ \mu_T = \mu_f + \mu_R + \mu_C $$ 

where $\mu_f$, $\mu_R$ and $\mu_C$, are, respectively, the attenuation coefficients of absorption by photoelectric effect, of
Rayleigh scattering and Compton scattering. As the three processes are independent, after a length $x$ (exponentially distributed) the process to occur will be process $i$, with probability:

$$ pi = \frac{\mu_i}{\mu_T} $$ 

In this work I only considered monodirectional photon beams and focused on the photon beam primary particles, that is, I did not follow the behavior of the secondary particles produced (whether they are photons or electrons).

## Monochromatic beam

Consider a monochromatic beam with an energy of 1 keV passing through an aluminum block of infinite thickness and coefficients: $\mu_f = 3.19 \times 10^3 cm^{-1}$, $\mu_R =6.09 cm^{-1} and $\mu_C = 3.83 \times 10^2 cm^{-1}.
Simulated the beam propagation inside the material using the Monte Carlo method. Calculated:

- thickness of material necessary to reduce the intensity of the primary beam to half that its initial value and compared it with the analytically predicted value;
- graph the fraction of photons that survive without interacting after a length x and compared as predicted analytically.

![fig1](https://github.com/21sult/Photon-Interactions-Monte-Carlo/assets/145617965/855c86b6-7bf3-4a08-adc8-eeb1d2bc741b)

![fig2](https://github.com/21sult/Photon-Interactions-Monte-Carlo/assets/145617965/6aaf0422-5a57-4fef-94fa-4ed1b5714017)


## Polychromatic Beam (X-Ray Tube)

For real situations of interest, the beam is polychromatic and the attenuation coefficients depend on the photon energy. In the absence of analytical expressions for the beam energy distribution and dependence of energy attenuation coefficients, tables obtained numerically or from experiments.

Tables for the linear attenuation coefficients for each interaction can be obtained from the NIST website (National Institute of Standards and Technology) through the link https://www.nist.gov/pml/xcom-photoncross-sections-database. Tables are available for all elements up to Z=92, as well as compounds or mixtures. When using these tables, it must be taken into account that the units of energy used are MeV and the tabulated quantities are $\mu / \rho$ in cm2/g, where $\rho$ is the density of the material (g/cm3). The application allows you to enter sets of energy values for which $\mu / \rho$ are calculated.

Consider the provided polychromatic X-ray beam (110kV.spec), using Aluminum as the medium of choice. I simulated a photon beam that follows this energy distribution and:

- Calculated the thickness of material required to reduce the intensity of the primary beam to half the
its initial value;
- Obtained a graph of the fraction of photons that survive without interacting after a length x;

![fig3](https://github.com/21sult/Photon-Interactions-Monte-Carlo/assets/145617965/3540476b-d47e-4072-aebb-d2a912e872c2)

