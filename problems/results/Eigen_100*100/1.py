"""
python /Users/wangyifeng/projects/diffusion_2d/problems/results/Eigen_100*100/1.py
"""

import vtk
import chigger

camera = vtk.vtkCamera()
camera.SetViewUp(0.0000000000, 1.0000000000, 0.0000000000)
camera.SetPosition(40.0000000000, 40.0000000000, 218.5640646055)
camera.SetFocalPoint(40.0000000000, 40.0000000000, 0.0000000000)

reader = chigger.exodus.ExodusReader('TWIGL_Twogroups_Eigenproblem_out.e')
reader.setOptions(block=['1', '2', '3'])

result = chigger.exodus.ExodusResult(reader)
result.setOptions(edge_color=[0, 0, 0], variable='flux_group2', block=['1', '2', '3'], local_range=True, camera=camera)

cbar = chigger.exodus.ExodusColorBar(result)
cbar.setOptions(colorbar_origin=(0.8, 0.25, 0.0))
cbar.setOptions('primary', lim=[0.0, 0.002778855146020534], font_color=[0, 0, 0], font_size=16)

window = chigger.RenderWindow(result, cbar)
window.setOptions(size=None, style=None, background=[1, 1, 1])
window.start()
