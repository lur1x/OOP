#include "HTMLDecodeCore.hpp"

const std::array<std::pair<std::string_view, char>, 5> HTML_ENTITIES = {{
                                                                                {"&quot;", '"'},
                                                                                {"&apos;", '\''},
                                                                                {"&lt;", '<'},
                                                                                {"&gt;", '>'},
                                                                                {"&amp;", '&'}
                                                                        }};


std::string HTMLDecode(std::string const& html) {

    std::string decodedHtml;

    size_t pos = 0;
    while (pos < html.size()) {

        size_t ampPos = html.find('&', pos);

        if (ampPos == std::string::npos) {
            decodedHtml.append(html, pos, html.size() - pos);
            break;
        }

        decodedHtml.append(html, pos, ampPos - pos);

        size_t semicolonPos = html.find(';', ampPos);

        if (semicolonPos == std::string::npos) {
            decodedHtml += '&';
            pos = ampPos + 1;
            continue;
        }

        std::string_view entity(&html[ampPos], semicolonPos - ampPos + 1);

        bool found = false;
        for (const auto& [htmlEntity, symbol] : HTML_ENTITIES) {
            if (entity == htmlEntity) {
                decodedHtml += symbol;
                pos = semicolonPos + 1;
                found = true;
                break;
            }
        }

        if (!found) {
            decodedHtml.append(entity);
            pos = semicolonPos + 1;
        }
    }

    return decodedHtml;
}
