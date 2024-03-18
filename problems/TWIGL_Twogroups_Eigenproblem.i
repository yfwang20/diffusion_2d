[Mesh]
  [generator]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 80
    ymax = 80
    nx = 80
    ny = 80
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
    [fission]
        order = CONSTANT
        family = MONOMIAL
    []
[]

[Kernels]
    [diffusion_group1]
      type = Diffusion_term_Twogroups_group1
      variable = flux_group1
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

    [fission_group1]
        type = Fission_Twogroups_Eigenproblem_group1
        variable = flux_group1
        otherflux_1 = flux_group2
        extra_vector_tags = 'eigen'
        coefficient = -1.0
    []


    [diffusion_group2]
      type = Diffusion_term_Twogroups_group2
      variable = flux_group2
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

    [fission_group2]
        type = Fission_Twogroups_Eigenproblem_group2
        variable = flux_group2
        otherflux_1 = flux_group1
        extra_vector_tags = 'eigen'
        coefficient = -1.0
    []


    [delayed_nucleus_c1_decay]
        type = DelayedNeutron_Decay
        variable = delayed_c1
        num = 1
    []

    [delayed_nucleus_c1_fission]
        type = DelayedNeutron_Fission
        variable = delayed_c1
        num = 1
        coefficient = -1.0
        flux_group1 = flux_group1
        flux_group2 = flux_group2
        extra_vector_tags = 'eigen'
    []
[]

[AuxKernels]
    [fission_aux]
        type = Fission_aux
        variable = fission
        flux_group1 = flux_group1
        flux_group2 = flux_group2
    []
[]

[Materials]
    [materail_1]
        type = Material_TWIGL_Twogroups
        block = '1'
        diffusion_coefficient_group1 = 1.4
        diffusion_coefficient_group2 = 0.4
        absorption_cross_section_group1 = 0.01
        absorption_cross_section_group2 = 0.15
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 0
        fission_cross_section_v_group1 = 0.007
        fission_cross_section_v_group2 = 0.2
        velocity_group1 = 10000000
        velocity_group2 = 200000
        beta = 0.0075
        beta_1 = 0.0075
        beta_2 = 0.0
        beta_3 = 0.0
        beta_4 = 0.0
        beta_5 = 0.0
        beta_6 = 0.0
        lambda_1 = 0.08
        lambda_2 = 0.0
        lambda_3 = 0.0
        lambda_4 = 0.0
        lambda_5 = 0.0
        lambda_6 = 0.0
    []

    [materail_2]
        type = Material_TWIGL_Twogroups
        block = '2'
        diffusion_coefficient_group1 = 1.4
        diffusion_coefficient_group2 = 0.4
        absorption_cross_section_group1 = 0.01
        absorption_cross_section_group2 = 0.15
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 0
        fission_cross_section_v_group1 = 0.007
        fission_cross_section_v_group2 = 0.2
        velocity_group1 = 10000000
        velocity_group2 = 200000
        beta = 0.0075
        beta_1 = 0.0075
        beta_2 = 0.0
        beta_3 = 0.0
        beta_4 = 0.0
        beta_5 = 0.0
        beta_6 = 0.0
        lambda_1 = 0.08
        lambda_2 = 0.0
        lambda_3 = 0.0
        lambda_4 = 0.0
        lambda_5 = 0.0
        lambda_6 = 0.0
    []

    [materail_3]
        type = Material_TWIGL_Twogroups
        block = '3'
        diffusion_coefficient_group1 = 1.3
        diffusion_coefficient_group2 = 0.5
        absorption_cross_section_group1 = 0.008
        absorption_cross_section_group2 = 0.05
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 0
        fission_cross_section_v_group1 = 0.003
        fission_cross_section_v_group2 = 0.06
        velocity_group1 = 10000000
        velocity_group2 = 200000
        beta = 0.0075
        beta_1 = 0.0075
        beta_2 = 0.0
        beta_3 = 0.0
        beta_4 = 0.0
        beta_5 = 0.0
        beta_6 = 0.0
        lambda_1 = 0.08
        lambda_2 = 0.0
        lambda_3 = 0.0
        lambda_4 = 0.0
        lambda_5 = 0.0
        lambda_6 = 0.0
    []
[]

[BCs]
    [right_group1]
        type = DirichletBC
        variable = flux_group1
        boundary = 'right'
        value = 0
    []

    [right_group2]
        type = DirichletBC
        variable = flux_group2
        boundary = 'right'
        value = 0
    []

    [top_group1]
        type = DirichletBC
        variable = flux_group1
        boundary = 'top'
        value = 0
    []

    [top_group2]
        type = DirichletBC
        variable = flux_group2
        boundary = 'top'
        value = 0
    []
[]

[Executioner]
    type = Eigenvalue
[]

[VectorPostprocessors]
  [eigenvalues]
    type = Eigenvalues
    execute_on = 'timestep_end'
  []
[]

[Postprocessors]
  [fnorm]
    type = ElementIntegralVariablePostprocessor
    variable = fission
    # execute on residual is important for nonlinear eigen solver!
    execute_on = linear
  [../]
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]