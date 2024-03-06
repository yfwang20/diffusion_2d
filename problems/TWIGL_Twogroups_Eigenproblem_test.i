[Mesh]
  [generator]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 80
    ymax = 80
    nx = 10
    ny = 10
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

    #[scattering_group1]
    #  type = Scattering_Twogroups_group1
    #  variable = flux_group1
    #  otherflux_1 = flux_group2
    #[]

    [fission_group1]
        type = Fission_Twogroups_group1
        variable = flux_group1
        otherflux_1 = flux_group2
        extra_vector_tags = 'eigen'
        coefficient = -1.0
    []

    [absorption_group2]
        type = Absorption_Twogroups_group2
        variable = flux_group2
    []

[]

[Materials]
    [materail_1]
        type = Material_TWIGL_Twogroups
        block = '1'
        diffusion_coefficient_group1 = 0.9
        diffusion_coefficient_group2 = 0.9
        absorption_cross_section_group1 = 0.08
        absorption_cross_section_group2 = 0.08
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 1
        fission_cross_section_v_group1 = 0.1035
        fission_cross_section_v_group2 = 0.1035
    []

    [materail_2]
        type = Material_TWIGL_Twogroups
        block = '2'
        diffusion_coefficient_group1 = 0.9
        diffusion_coefficient_group2 = 0.9
        absorption_cross_section_group1 = 0.08
        absorption_cross_section_group2 = 0.08
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 1
        fission_cross_section_v_group1 = 0.1035
        fission_cross_section_v_group2 = 0.1035
    []

    [materail_3]
        type = Material_TWIGL_Twogroups
        block = '3'
        diffusion_coefficient_group1 = 0.9
        diffusion_coefficient_group2 = 0.9
        absorption_cross_section_group1 = 0.029
        absorption_cross_section_group2 = 0.029
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 1
        fission_cross_section_v_group1 = 0.0315
        fission_cross_section_v_group2 = 0.0315
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

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]