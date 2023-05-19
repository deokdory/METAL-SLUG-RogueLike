#include "Framework.h"
#include "TileSet.h"

bool TileSet::GUI()
{
  bool selected = false;

  ImGui::Begin("TileSet");
  {
    {
      int count = 0;
      for (UINT y = 0; y < tileYCount; y++)
      {
        for (uint x = 0; x < tileXCount; x++)
        {
          ImVec2 startUV = { tileUV.x * x, tileUV.y * y };
          ImVec2 endUV = ImVec2(startUV.x + tileUV.x, startUV.y + tileUV.y);

          ImGui::PushID(count);
          if (ImGui::ImageButton(tileSRV, ImVec2(24, 24), startUV, endUV))
          {
            selectedStartUV = Vector2(startUV.x, startUV.y);
            selected = true;
          }

          count++;
          ImGui::PopID();

          if (count % tileXCount != 0)
            ImGui::SameLine();
        }
      }
    }
  }
  ImGui::End();

  ImGui::Begin("Draw");
  {
    ImVec2 selectedEndUV = ImVec2{ selectedStartUV.x + tileUV.x, selectedStartUV.y + tileUV.y };
    ImGui::SameLine();
    ImGui::Image(tileSRV, ImVec2(32, 32), ImVec2(selectedStartUV.x, selectedStartUV.y), selectedEndUV);
  }
  ImGui::End();

  return selected;
}

TileSet::TileSet(std::wstring filePath, UINT tileXCount, UINT tileYCount)
  : themeName(themeName), tileXCount(tileXCount), tileYCount(tileYCount)
{
  Texture2D* tex = new Texture2D(filePath);
  tileSRV = tex->GetSRV();

  singlePixelUV = { 1.0f / tex->GetWidth(), 1.0f / tex->GetHeight() };
  SAFE_DELETE(tex);

  tileUV = Vector2(1.0f / (float)tileXCount, 1.0f / (float)tileYCount);
}

TileSet::~TileSet()
{
}
