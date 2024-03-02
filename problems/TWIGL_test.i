[Mesh]
  [generator]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 80
    ymax = 80
    nx = 10
    ny = 10
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
        type = Absorption
        variable = flux
    []

    [diffusion]
        type = Diffusion_term
        variable = flux
    []

    [fission]
        type = Fission
        variable = flux
        extra_vector_tags = 'eigen'
    []
[]

[Materials]
    [materail_1]
        type = Material_1
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.08
        fission_cross_section_v = 0.1035
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

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]