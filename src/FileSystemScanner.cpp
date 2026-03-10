#include "../include/FileSystemScanner.h"

//вектор с путями к файлам и директориям, потом отправляет их в TreeBuilder
std::vector<std::filesystem::path>
FileSystemScanner::Scan(
    const std::filesystem::path& root,
    std::optional<int> max_depth
)
{
    std::vector<std::filesystem::path> result;

    try
    {
        if (!std::filesystem::exists(root)) {
            return result;
        }

        result.push_back(root);

        if (!std::filesystem::is_directory(root)) {
            return result;
        }

        //сканирование с итератором
        std::filesystem::recursive_directory_iterator current(
            root,
            std::filesystem::directory_options::skip_permission_denied //чтобы не падалор если нет доступа к папке
        );
        std::filesystem::recursive_directory_iterator end;

        while (current != end) //цикл обхода файлов и папок
        {
            if (max_depth.has_value() && current.depth() + 1 > max_depth.value()) //+1 чтобы от root уйти
            {
                current.disable_recursion_pending(); //не идти глубже max_depth
            }
            else {
                result.push_back(current->path());
            }

            ++current;
        }
    }

    //если возникли проблемы то вернуть что успело пройти
    catch (std::filesystem::filesystem_error&) {
        return result;
    }

    return result;
}
