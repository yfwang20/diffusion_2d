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
    [flux]
        order = FIRST
        family = LAGRANGE
    []
[]


[Kernels]
    [absorption]
        type = Absorption_Singlegroup
        variable = flux
    []

    [diffusion]
        type = Diffusion_term_Singlegroup
        variable = flux
    []

    [fission]
        type = Fission_Singlegroup
        variable = flux
        extra_vector_tags = 'eigen'
        coefficient = -1.0
    []
[]

[Materials]
    [materail_1]
        type = Material_TWIGL_Singlegroup
        block = '1'
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.08
        fission_cross_section_v = 0.1035
    []

    [materail_2]
        type = Material_TWIGL_Singlegroup
        block = '2'
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.08
        fission_cross_section_v = 0.1035
    []

    [materail_3]
        type = Material_TWIGL_Singlegroup
        block = '3'
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.029
        fission_cross_section_v = 0.0315
    []
[]

[BCs]
    [right]
        type = DirichletBC
        variable = flux
        boundary = 'right'
        value = 0
    []

    [top]
        type = DirichletBC
        variable = flux
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