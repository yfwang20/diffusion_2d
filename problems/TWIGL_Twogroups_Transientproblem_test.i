[Mesh]
  [generator]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 80
    ymax = 80
    nx = 100
    ny = 100
  []
  [subdomain1]
    type = SubdomainBoundingBoxGenerator
    input = generator
    bottom_left = '0 0 0'
    top_right = '24 24 0'
    block_id = 3
  []
  [subdomain2]
    type = SubdomainBoundingBoxGenerator
    input = subdomain1
    bottom_left = '24 0 0'
    top_right = '56 24 0'
    block_id = 2
  []
  [subdomain3]
    type = SubdomainBoundingBoxGenerator
    input = subdomain2
    bottom_left = '0 24 0'
    top_right = '24 56 0'
    block_id = 2
  []
  [subdomain4]
    type = SubdomainBoundingBoxGenerator
    input = subdomain3
    bottom_left = '24 24 0'
    top_right = '56 56 0'
    block_id = 1
  []
  [subdomain5]
    type = SubdomainBoundingBoxGenerator
    input = subdomain4
    bottom_left = '56 0 0'
    top_right = '80 80 0'
    block_id = 3
  []
  [subdomain6]
    type = SubdomainBoundingBoxGenerator
    input = subdomain5
    bottom_left = '0 56 0'
    top_right = '56 80 0'
    block_id = 3
  []
[]

[Variables]
    [flux_group1]
        order = FIRST
        family = LAGRANGE
    []

    [flux_group2]
        order = FIRST
        family = LAGRANGE
    []

    [delayed_c1]
        order = FIRST
        family = LAGRANGE
    []
[]

[AuxVariables]
    [delayed_nucleus]
        order = CONSTANT
        family = MONOMIAL
    []
[]

[Kernels]
    [timederivative_group1]
        type = TimeDerivative_group1
        variable = flux_group1
    []

    [diffusion_group1]
        type = Diffusion_term_Twogroups_group1
        variable = flux_group1
    []

    [fission_group1]
        type = Fission_Twogroups_Transientproblem_group1
        variable = flux_group1
        coefficient = -1.0
        keff = 0.91322
        otherflux_1 = flux_group2
    []

    [absorption_group1]
        type = Absorption_Twogroups_group1
        variable = flux_group1
    []

    [scattering_group1]
        type = Scattering_Twogroups_group1
        variable = flux_group1
        otherflux_1 = flux_group2
    []

    [delayedneutronsources_group1]
        type = Delayed_NeutronSources_group1
        variable = flux_group1
        delayed_nucleus = delayed_nucleus
    []

    
    [timederivative_group2]
        type = TimeDerivative_group2
        variable = flux_group2
    []

    [diffusion_group2]
        type = Diffusion_term_Twogroups_group2
        variable = flux_group2
    []

    [fission_group2]
        type = Fission_Twogroups_Transientproblem_group2
        variable = flux_group2
        coefficient = -1.0
        keff = 0.91322
        otherflux_1 = flux_group1
    []

    [absorption_group2]
        type = Absorption_Twogroups_group2
        variable = flux_group2
    []

    [scattering_group2]
        type = Scattering_Twogroups_group2
        variable = flux_group2
        otherflux_1 = flux_group1
    []

    [delayedneutronsources_group2]
        type = Delayed_NeutronSources_group2
        variable = flux_group2
        delayed_nucleus = delayed_nucleus
    []

    [delayed_nucleus_c1_timederivate]
        type = DelayedNeutron_TimeDerivate
        variable = delayed_c1
    []

    [delayed_nucleus_c1_decayandfission]
        type = DelayedNeutron_Decayandfission
        variable = delayed_c1
        num = 1
        keff = 0.91322
        flux_group1 = flux_group1
        flux_group2 = flux_group2
    []

[]